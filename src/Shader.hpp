#pragma once
#include <GL/glew.h>
#include <string>

class Shader
{
public:
    Shader();
    ~Shader();

    bool load(const std::string& vert_name, const std::string& frag_name);
    void unLoad();
    void setActive();
    void setMatUniform(const char* name, const class Mat4& mat);

private:
    bool compileShader(const std::string& file_name, GLenum shader_type, GLuint& out_shader);
    bool isCompiled(GLuint shader);
    bool isValidProgram();  // �v���O�����̃����N�m�F
    
    // �V�F�[�_�I�u�W�F�N�g��ID�i�[
    GLuint vertex_shader_;
    GLuint frag_shader_;
    GLuint shader_program_;
};