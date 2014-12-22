
#ifndef HPP_TEXTURE
#define HPP_TEXTURE

#include <string>
#include <GL/gl.h>

namespace glimac {
    class Texture {
    	GLuint tex_id;

	public:
	    static Texture load(std::string path);
	    void free();

	    GLuint getId() const;
    };
}

#endif

