#pragma once

class VertexArray
{
public:
    VertexArray(const float* verts, unsigned int num_verts, const unsigned int* indices, unsigned int num_indices);
    ~VertexArray();

    void setActive();

    unsigned int getNumVerts() const { return num_verts_; }
    unsigned int getNumIndices() const { return num_indices_; }

private:
    unsigned int num_verts_;  // 頂点数
    unsigned int num_indices_;  // インデックス数
    unsigned int vertex_buffer_;  // 頂点バッファのID
    unsigned int index_buffer_;  // インデックスバッファのID
    unsigned int vertex_array_;  // 頂点配列のID
};