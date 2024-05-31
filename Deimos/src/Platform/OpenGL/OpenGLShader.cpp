#include "dmpch.h"
#include "OpenGLShader.h"

#include <glm/glm/gtc/type_ptr.hpp>

namespace Deimos {

    static GLenum getShaderTypeFromString(const std::string &str) {
        if (str == "fragment" || str == "pixel")
            return GL_FRAGMENT_SHADER;
        else if (str == "vertex")
            return GL_VERTEX_SHADER;
        else DM_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string &filepath) {
        std::string src = readFile(filepath);
        std::unordered_map<GLenum, std::string> shaderSrc = preprocess(src);
        compile(shaderSrc);

        // extract name from filepath
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind(".");
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_name = filepath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
            : m_name(name) {
        std::unordered_map<GLenum, std::string> shaderSrc;
        shaderSrc[GL_VERTEX_SHADER] = vertexSrc;
        shaderSrc[GL_FRAGMENT_SHADER] = fragmentSrc;
        compile(shaderSrc);
    }

    std::string OpenGLShader::readFile(const std::string &filepath) {
        std::ifstream in(filepath, std::ios::in | std::ios::binary);

        std::string res;
        if (in) {
            in.seekg(0, std::ios::end);
            res.resize(in.tellg()); // find how many symbols in file
            in.seekg(0, std::ios::beg);
            in.read(&res[0], res.size());
            in.close();
            return res;
        }
        DM_CORE_ERROR("Could not open file '{0}'", filepath);
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::preprocess(const std::string &source) {
        std::unordered_map<GLenum, std::string> shaderSources;

        const char *typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);

        while (pos != std::string::npos) {
            size_t eol = source.find_first_of("\r\n", pos);
            DM_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            DM_CORE_ASSERT(getShaderTypeFromString(type), "Invalid shader type specified!");

            pos = source.find(typeToken, eol);
            std::string src;
            if (pos != std::string::npos)
                src = source.substr(eol, pos - eol);
            else
                src = source.substr(eol);
            shaderSources[getShaderTypeFromString(type)] = src;
        }
        return shaderSources;
    }

    void OpenGLShader::compile(const std::unordered_map<GLenum, std::string> &shaderSources) {
        GLuint program = glCreateProgram();
        DM_ASSERT(shaderSources.size() <= 2, "We only support 2 shader for now");
        std::array<GLuint, 2> glShaderIDs{};
        int glShaderIDIndex = 0;
        for (auto &[key, value]: shaderSources) {
            GLuint shader = glCreateShader(key);

            const GLchar *source = (const GLchar *) value.c_str();
            glShaderSource(shader, 1, &source, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                // We don't need the shader anymore.
                glDeleteShader(shader);

                DM_CORE_ERROR("{0}", infoLog.data());
                DM_CORE_ASSERT(false, "Shader compilation failure!");
                return;
            }
            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++] = shader;
        }
        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *) &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);
            for (auto &v: glShaderIDs) {
                glDeleteShader(v);
            }

            DM_CORE_ERROR("{0}", infoLog.data());
            DM_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        for (auto &v: glShaderIDs) {
            glDetachShader(program, v);
        }

        m_rendererID = program;
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

    void OpenGLShader::uploadUniformInt(const std::string &name, int value) {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::uploadUniformFloat(const std::string &name, float value) {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::uploadUniformFloat2(const std::string &name, const glm::vec2 &value) {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::uploadUniformFloat3(const std::string &name, const glm::vec3 &value) {
        GLint location = glGetUniformLocation(m_rendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::uploadUniformFloat4(const std::string &name, const glm::vec4 &value) {
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
