#pragma once
#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


unsigned int texture_from_file(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
    // model data 
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh>    meshes;
    std::string directory;
    bool gamma_correction;

    // constructor, expects a filepath to a 3D model.
    Model(std::string const& path, bool gamma);
    ~Model();
    void draw(Shader*& shader);
    void set_flip_vertically_img();
private:
    void load_model(std::string const& path);
    void process_node(aiNode* node, const aiScene* scene);
    Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type, std::string type_name);
};

unsigned int texture_from_file(const char* path, const std::string& directory, bool gamma);