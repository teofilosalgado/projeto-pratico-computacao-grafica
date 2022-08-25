#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

Shader::Shader(const char* vertex_file_path, const char* fragment_file_path) {
	// Cria os shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Lê o shader de vértices do arquivo
	std::cout << "Lendo shader de vértices: " << vertex_file_path << std::endl;
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		std::cerr << "Erro ao ler o arquivo: " << vertex_file_path << std::endl;
	}
	std::cout << "Arquivo lido com sucesso" << std::endl;

	// Lê o shader de fragmentos do arquivo
	std::cout << "Lendo shader de fragmentos: " << fragment_file_path << std::endl;
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	else {
		std::cerr << "Erro ao ler o arquivo: " << fragment_file_path << std::endl;
	}
	std::cout << "Arquivo lido com sucesso" << std::endl;

	// Variáveis para armazenar resultados de compilações e suas mensagens
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compila o shader de vértices
	std::cout << "Compilando shader de vértices" << std::endl;
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Verifica o shader de vértices
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cerr << "Erro ao compilar shader de vértices: " << &VertexShaderErrorMessage[0] << std::endl;
	}

	// Compila o shader de fragmentos
	std::cout << "Compilando shader de fragmentos" << std::endl;
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Verifica o shader de fragmentos
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		std::cerr << "Erro ao compilar shader de fragmentos: " << &FragmentShaderErrorMessage[0] << std::endl;
	}

	// Linka os programas
	std::cout << "Vinculando os programas" << std::endl;
	program_id = glCreateProgram();
	glAttachShader(program_id, VertexShaderID);
	glAttachShader(program_id, FragmentShaderID);
	glLinkProgram(program_id);

	// Verifica os programas
	glGetProgramiv(program_id, GL_LINK_STATUS, &Result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(program_id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cerr << "Erro ao linkar programas: " << &ProgramErrorMessage[0] << std::endl;
	}

	// Limpa os shaders da memória
	glDetachShader(program_id, VertexShaderID);
	glDetachShader(program_id, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	std::cout << "Shaders vinculados com sucesso" << std::endl;
}