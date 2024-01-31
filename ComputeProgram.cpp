#include "ComputeProgram.h"

ComputeProgram::ComputeProgram()
{
	_programID = 0;
	clear();
}

void ComputeProgram::createFromFile(std::string fileLocation)
{
	std::string shaderString = readFile(fileLocation);

	const char* shaderCode = shaderString.c_str();

	compileShader(shaderCode);
}

std::string ComputeProgram::readFile(std::string fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation.c_str(), std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "Failed to read %s! File doesn't exist." << fileLocation;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void ComputeProgram::compileShader(std::string shaderCode)
{
	_programID = glCreateProgram();

	if (!_programID)
	{
		std::cout << "Error creating shader program!\n";
		return;
	}

	addShader(_programID, shaderCode, GL_COMPUTE_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(_programID);
	glGetProgramiv(_programID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(_programID, sizeof(eLog), NULL, eLog);
		std::cout << "Error linking program: '" << eLog << "'\n";	
		return;
	}

	glValidateProgram(_programID);
	glGetShaderiv(_programID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(_programID, sizeof(eLog), NULL, eLog);
		std::cout << "Error validating program: '" << eLog << "'\n";
		return;
	}
}

void ComputeProgram::use()
{
	glUseProgram(_programID);
}

void ComputeProgram::clear()
{
	if (_programID != 0)
	{
		glDeleteShader(_programID);
		_programID = 0;
	}

}

void ComputeProgram::addShader(GLuint theProgram, std::string shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode.c_str();

	GLint codeLength[1];
	codeLength[0] = (GLint)strlen(shaderCode.c_str());

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		std::cout << "Error compiling the " << shaderType << " shader: '" << eLog << "'\n";
		return;
	}

	glAttachShader(theProgram, theShader);
}

ComputeProgram::~ComputeProgram()
{
	clear();
}

