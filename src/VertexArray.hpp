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
    unsigned int num_verts_;  // ���_��
    unsigned int num_indices_;  // �C���f�b�N�X��
    unsigned int vertex_buffer_;  // ���_�o�b�t�@��ID
    unsigned int index_buffer_;  // �C���f�b�N�X�o�b�t�@��ID
    unsigned int vertex_array_;  // ���_�z���ID
};