#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// COMPILE SHADERS
	GLuint vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");

	// LINK PROGRAM
	Shader::id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	glValidateProgram(id);
	checkCompileErrors(id, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() const
{
	glUseProgram(id);
}

void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec) const
{
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &vec[0]);
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	int success;
	int errorMessageLength;
	char* errorMessage;
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorMessageLength);
			errorMessage = (char*)alloca(errorMessageLength * sizeof(char));
			glGetShaderInfoLog(shader, errorMessageLength, &errorMessageLength, errorMessage);
			std::cout << "Failed to compile shader!" << std::endl;
			std::cout << errorMessage << std::endl;
			glDeleteShader(shader);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &errorMessageLength);
			errorMessage = (char*)alloca(errorMessageLength * sizeof(char));
			glGetProgramInfoLog(shader, errorMessageLength, &errorMessageLength, errorMessage);
			std::cout << "Failed to link program!" << std::endl;
			std::cout << errorMessage << std::endl;
			glDeleteProgram(shader);
		}
	}
}