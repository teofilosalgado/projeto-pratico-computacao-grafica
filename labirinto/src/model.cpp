#define TINYOBJLOADER_IMPLEMENTATION
#include "model.h"


Model::Model(const std::string& objPath, const std::string& objFilename)
{
	// Inicializando o leitor de Wavefront
	tinyobj::ObjReaderConfig reader_config;
	reader_config.mtl_search_path = objPath;

	const std::string& model_file_path = objPath + "\\" + objFilename;
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
	for (size_t shapeIndex = 0; shapeIndex < shapes.size(); shapeIndex++) {
		size_t indexOffset = 0;
		for (size_t faceIndex = 0; faceIndex < shapes[shapeIndex].mesh.num_face_vertices.size(); faceIndex++) {
			int faceVertices = shapes[shapeIndex].mesh.num_face_vertices[faceIndex];

			for (size_t vertexIndex = 0; vertexIndex < faceVertices; vertexIndex++) {
				tinyobj::index_t idx = shapes[shapeIndex].mesh.indices[indexOffset + vertexIndex];

				glm::vec3 vertex = glm::vec3(attrib.vertices[3 * idx.vertex_index + 0], attrib.vertices[3 * idx.vertex_index + 1], attrib.vertices[3 * idx.vertex_index + 2]);
				glm::vec2 uv = glm::vec2(attrib.texcoords[2 * idx.texcoord_index + 0], attrib.texcoords[2 * idx.texcoord_index + 1]);
				glm::vec3 normal = glm::vec3(attrib.normals[3 * idx.normal_index + 0], attrib.normals[3 * idx.normal_index + 1], attrib.normals[3 * idx.normal_index + 2]);

				vertices.push_back(vertex);
				uvs.push_back(uv);
				normals.push_back(normal);
			}
			indexOffset += faceVertices;
		}

		std::vector<tinyobj::index_t> meshIndices = shapes[shapeIndex].mesh.indices;
		for (size_t meshIndex = 0; meshIndex < meshIndices.size(); meshIndex++)
		{
			indices.push_back(meshIndex);
		}
	}
	std::cout << "Modelo lido com sucesso" << std::endl;
}