#include "dmpch.h"
#include "OpenGLShader.h"

#include <GLAD/include/glad/glad.h>

#include <glm/glm/gtc/type_ptr.hpp>

namespace Deimos {

    OpenGLShader::OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc) {
        // Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);


        const GLchar *source = (const GLchar *) vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            DM_CORE_ERROR("{0}", infoLog.data());
            DM_CORE_ASSERT(false, "Vertex shader compilation failure!");

            return;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = (const GLchar *) fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            DM_CORE_ERROR("{0}", infoLog.data());
            DM_CORE_ASSERT(false, "Fragment shader compilation failure!");
            return;
        }

        // Get a program object
        m_rendererID = glCreateProgram();
        GLuint program = m_rendererID;

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *) &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            DM_CORE_ERROR("{0}", infoLog.data());
            DM_CORE_ASSERT(false, "Shader link failure!");

            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);

    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_rendererID);
    }

    void OpenGLShader::bind() const {
        glUseProgram(m_rendererID);
    }

    void OpenGLShader::unbind() const {
        glUseProgram(0);
    }
    void OpenGLShader::uploadFloat(const std::string &name, float value) {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::uploadInt(const std::string &name, int value) {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::uploadFloat2(const std::string &name, const glm::vec2 &value) {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::uploadFloat3(const std::string &name, const glm::vec3 &value) {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::uploadFloat4(const std::string &name, const glm::vec4& value) {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::uploadUniformMat3(const std::string &name, const glm::mat3 &matrix) {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glad_glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::uploadUniformMat4(const std::string &name, const glm::mat4 &matrix) {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glad_glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}