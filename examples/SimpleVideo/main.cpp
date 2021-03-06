/**
 * @author  Steven Lovegrove
 * Copyright (C) 2010  Steven Lovegrove
 *                     Imperial College London
 **/

#include <pangolin/pangolin.h>

void SetGlFormat(GLint& glchannels, GLenum& glformat, const pangolin::VideoPixelFormat& fmt)
{
    switch( fmt.channels) {
    case 1: glchannels = GL_LUMINANCE; break;
    case 3: glchannels = GL_RGB; break;
    case 4: glchannels = GL_RGBA; break;
    default: throw std::runtime_error("Unable to display video format");
    }

    switch (fmt.channel_bits[0]) {
    case 8: glformat = GL_UNSIGNED_BYTE; break;
    case 16: glformat = GL_UNSIGNED_SHORT; break;
    case 32: glformat = GL_FLOAT; break;
    default: throw std::runtime_error("Unknown channel format");
    }
}

void VideoSample(const std::string uri)
{
    // Setup Video Source
    pangolin::VideoInput video(uri);
    const pangolin::VideoPixelFormat vid_fmt = video.PixFormat();
    const unsigned w = video.Width();
    const unsigned h = video.Height();
#if !defined(HAVE_GLES) || defined(HAVE_GLES_2)
    const float scale = video.VideoUri().Get<float>("scale", 1.0f);
    const float bias  = video.VideoUri().Get<float>("bias", 0.0f);
#endif

    // Work out appropriate GL channel and format options
    GLint glchannels;
    GLenum glformat;
    SetGlFormat(glchannels, glformat, vid_fmt);
    
    // Create OpenGL window
    pangolin::CreateWindowAndBind("Main",w,h);

    // Create viewport for video with fixed aspect
    pangolin::View& vVideo = pangolin::Display("Video").SetAspect((float)w/h);

    // OpenGl Texture for video frame.
    pangolin::GlTexture texVideo(w,h,glchannels,false,0,glchannels,glformat);

    unsigned char* img = new unsigned char[video.SizeBytes()];

    for(int frame=0; !pangolin::ShouldQuit(); ++frame)
    {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        if( video.GrabNext(img,true) ) {
            texVideo.Upload( img, glchannels, glformat );
        }

        // Activate video viewport and render texture
        vVideo.Activate();
#if !defined(HAVE_GLES) || defined(HAVE_GLES_2)
        pangolin::GlSlUtilities::Scale(scale, bias);
        texVideo.RenderToViewportFlipY();
        pangolin::GlSlUtilities::UseNone();
#else
        texVideo.RenderToViewportFlipY();
#endif

        // Swap back buffer with front and process window events via GLUT
        pangolin::FinishFrame();
    }

    delete[] img;
}


int main( int argc, char* argv[] )
{
    std::string uris[] = {
        "dc1394:[fps=30,dma=10,size=640x480,iso=400]//0",
        "convert:[fmt=RGB24]//v4l:///dev/video0",
        "convert:[fmt=RGB24]//v4l:///dev/video1",
        "openni:[img1=rgb]//",
        "test:[size=160x120,n=1,fmt=RGB24]//"
        ""
    };

    if( argc > 1 ) {
        const std::string uri = std::string(argv[1]);
        VideoSample(uri);
    }else{
        std::cout << "Usage  : SimpleRecord [video-uri]" << std::endl << std::endl;
        std::cout << "Where video-uri describes a stream or file resource, e.g." << std::endl;
        std::cout << "\tfile:[realtime=1]///home/user/video/movie.pvn" << std::endl;
        std::cout << "\tfile:///home/user/video/movie.avi" << std::endl;
        std::cout << "\tfiles:///home/user/seqiemce/foo%03d.jpeg" << std::endl;
        std::cout << "\tdc1394:[fmt=RGB24,size=640x480,fps=30,iso=400,dma=10]//0" << std::endl;
        std::cout << "\tdc1394:[fmt=FORMAT7_1,size=640x480,pos=2+2,iso=400,dma=10]//0" << std::endl;
        std::cout << "\tv4l:///dev/video0" << std::endl;
        std::cout << "\tconvert:[fmt=RGB24]//v4l:///dev/video0" << std::endl;
        std::cout << "\tmjpeg://http://127.0.0.1/?action=stream" << std::endl;
        std::cout << "\topenni:[img1=rgb]//" << std::endl;
        std::cout << std::endl;

        // Try to open some video device
        for(int i=0; !uris[i].empty(); ++i )
        {
            try{
                std::cout << "Trying: " << uris[i] << std::endl;
                VideoSample(uris[i]);
                return 0;
            }catch(pangolin::VideoException) { }
        }
    }

    return 0;
}
