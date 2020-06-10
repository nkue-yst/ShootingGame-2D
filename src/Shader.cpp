#include "Shader.hpp"
#include <fstream>
#include <SDL.h>
#include <sstream>
#include "Math.hpp"

Shader::Shader()
    :vertex_shader_(0)
    , frag_shader_(0)
    , shader_program_(0)
{

}

Shader::~Shader()
{

}

bool Shader::load(const std::string& vert_name, const std::string& frag_name)
{
    if (!compileShader(vert_name, GL_VERTEX_SHADER, vertex_shader_) ||
        !compileShader(frag_name, GL_FRAGMENT_SHADER, frag_shader_))
    {
        return false;
    }

    /* シェーダをリンクしてシェーダプログラムを作成 */
    shader_program_ = glCreateProgram();
    glAttachShader(shader_program_, vertex_shader_);
    glAttachShader(shader_program_, frag_shader_);
    glLinkProgram(shader_program_);

    if (!isValidProgram())
    {
        return false;
    }

    return true;
}

void Shader::unLoad()
{
    glDeleteProgram(shader_program_);
    glDeleteShader(frag_shader_);
    glDeleteShader(vertex_shader_);
}

void Shader::setActive()
{
    glUseProgram(shader_program_);
}

void Shader::setMatUniform(const char* name, const Mat4& mat)
{
    GLuint loc_id = glGetUniformLocation(shader_program_, name);
    glUniformMatrix4fv(
        loc_id,
        1,
        GL_TRUE,
        mat.getPointer()
    );
}

bool Shader::compileShader(const std::string& file_name, GLenum shader_type, GLuint& out_shader)
{
    std::ifstream shader_file(file_name);
    if (shader_file.is_open())
    {
        std::stringstream s;
        s << shader_file.rdbuf();
        std::string contents = s.str();
        const char* contents_char = contents.c_str();

        out_shader = glCreateShader(shader_type);
        glShaderSource(out_shader, 1, &(contents_char), nullptr);
        glCompileShader(out_shader);

        if (!isCompiled(out_shader))
        {
            SDL_Log("Failed to compile %s.", file_name.c_str());
            return false;
        }
    }
    else
    {
        SDL_Log("Failed to find %s.", file_name.c_str());
        return false;
    }

    return true;
}

bool Shader::isCompiled(GLuint shader)
{
    GLint status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buf[512];
        memset(buf, 0, 512);
        glGetShaderInfoLog(shader, 511, nullptr, buf);
        SDL_Log("Failed to compile GLSL. : \n%s", buf);
        return false;
    }

    return true;
}

bool Shader::isValidProgram()
{
    GLint status;

    glGetProgramiv(shader_program_, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buf[512];
        memset(buf, 0, 512);
        glGetProgramInfoLog(shader_program_, 511, nullptr, buf);
        SDL_Log("Failed to link GLSL. : \n%s", buf);
        return false;
    }

    return true;
}