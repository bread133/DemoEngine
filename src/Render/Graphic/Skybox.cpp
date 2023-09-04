#include "Skybox.h"

Skybox::Skybox(std::vector<std::string> faces, Shader* shader)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), &skybox_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    load(faces, shader);
}

Skybox::~Skybox()
{
    delete[] skybox_vertices;
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Skybox::load(std::vector<std::string> faces, Shader* shader)
{
	skybox_texture = load_cubemap(faces);
}

void Skybox::draw(Shader* shader, Camera* camera, int WIDTH, int HEIGHT, glm::vec3 translation, glm::vec3 scale)
{
    glDepthFunc(GL_LEQUAL);
    //glDepthMask(GL_FALSE);
    shader->use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, translation);
    model = glm::scale(model, scale);

    shader->set_mat4("view", glm::mat4(glm::mat3(camera->get_view_matrix())));
    shader->set_mat4("projection", camera->get_projection_matrix(WIDTH, HEIGHT));
    shader->set_mat4("model", model);
    
    glBindVertexArray(vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    //glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}
