#include "VertexArray.hpp"
#include <GL/glew.h>

VertexArray::VertexArray(const float* verts, unsigned int num_verts, const unsigned int* indices, unsigned int num_indices)
    :num_verts_(num_verts)
    ,num_indices_(num_indices)
{
    // 頂点配列オブジェクトの作成
    glGenVertexArrays(1, &vertex_array_);
    glBindVertexArray(vertex_array_);

    // 頂点バッファの作成
    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(
        GL_ARRAY_BUFFER,
        num_verts * 3 * sizeof(float),
        verts,
        GL_STATIC_DRAW
    );

    // インデックスバッファの作成
    glGenBuffers(1, &index_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        num_indices * sizeof(unsigned int),
        indices,
        GL_STATIC_DRAW
    );
    
    // 頂点属性の設定
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 3,
        0
    );
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &index_buffer_);
    glDeleteBuffers(1, &vertex_buffer_);
    glDeleteVertexArrays(1, &vertex_array_);
}

void VertexArray::setActive()
{
    glBindVertexArray(vertex_array_);
}