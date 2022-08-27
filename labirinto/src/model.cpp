#define TINYOBJLOADER_IMPLEMENTATION
#include "model.h"

Model::Model(const std::string& model_path, const std::string& model_file_name)
{
	// Inicializando o leitor de Wavefront
	tinyobj::ObjReaderConfig reader_config;
	reader_config.mtl_search_path = model_path;

	const std::string& model_file_path = model_path + "\\" + model_file_name;
	std::cout << "Lendo modelo: " << model_file_path << std::endl;
	tinyobj::ObjReader reader;
	if (!reader.ParseFromFile(model_file_path, reader_config)) {
		std::cerr << "Erro ao ler arquivo: ";
		if (!reader.Error().empty()) {
			std::cerr << reader.Error();
		}
		std::cerr << std::endl;
	}
	if (!reader.Warning().empty()) {
		std::cout << "Warning ao ler arquivo: " << reader.Warning() << std::endl;
	}

	const tinyobj::attrib_t& attrib = reader.GetAttrib();
	std::vector<tinyobj::shape_t> shapes = reader.GetShapes();
	std::vector<tinyobj::material_t> materials = reader.GetMaterials();

	// Itera sobre as formas, vértices e indíces
	for (size_t shape_index = 0; shape_index < shapes.size(); shape_index++) {
		size_t index_offset = 0;
		for (size_t face_index = 0; face_index < shapes[shape_index].mesh.num_face_vertices.size(); face_index++) {
			int face_vertices = shapes[shape_index].mesh.num_face_vertices[face_index];

			for (size_t vertex_index = 0; vertex_index < face_vertices; vertex_index++) {
				tinyobj::index_t idx = shapes[shape_index].mesh.indices[index_offset + vertex_index];

				glm::vec3 vertex = glm::vec3(attrib.vertices[3 * idx.vertex_index + 0], attrib.vertices[3 * idx.vertex_index + 1], attrib.vertices[3 * idx.vertex_index + 2]);
				glm::vec2 uv = glm::vec2(attrib.texcoords[2 * idx.texcoord_index + 0], attrib.texcoords[2 * idx.texcoord_index + 1]);
				glm::vec3 normal = glm::vec3(attrib.normals[3 * idx.normal_index + 0], attrib.normals[3 * idx.normal_index + 1], attrib.normals[3 * idx.normal_index + 2]);

				vertices.push_back(vertex);
				uvs.push_back(uv);
				normals.push_back(normal);
			}
			index_offset += face_vertices;
		}

		std::vector<tinyobj::index_t> mesh_indices = shapes[shape_index].mesh.indices;
		for (size_t mesh_index = 0; mesh_index < mesh_indices.size(); mesh_index++)
		{
			indices.push_back(mesh_index);
		}
	}
	std::cout << "Modelo lido com sucesso" << std::endl;
}