#pragma once

#include <algorithm>
#include <string>
#include <chrono>
#include <iomanip>
#include <fstream>

#include <thread>

namespace Deimos {
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult {
		std::string name;
		FloatingPointMicroseconds start;
		std::chrono::microseconds elapsedTime;
		std::thread::id threadID;
	};

	struct InstrumentationSession {
		std::string name;
	};

	class Instrumentor {
	private:
		InstrumentationSession* m_currentSession;
		std::ofstream m_outputStream;
		int m_profileCount;
	public:
		Instrumentor() : m_currentSession(nullptr), m_profileCount(0) {
		}

		void beginSession(const std::string& name, const std::string& filepath = "results.json") {
			m_outputStream.open(filepath);
			writeHeader();
			m_currentSession = new InstrumentationSession{ name };
		}

		void endSession() {
			writeFooter();
			m_outputStream.close();
			delete m_currentSession;
			m_currentSession = nullptr;
			m_profileCount = 0;
		}

		void writeProfile(const ProfileResult& result) {
			if (m_profileCount++ > 0)
				m_outputStream << ",";

			std::string name = result.name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_outputStream << std::setprecision(3) << std::fixed;
			m_outputStream << "{";
			m_outputStream << "\"cat\":\"function\",";
			m_outputStream << "\"dur\":" << (result.elapsedTime.count()) << ',';
			m_outputStream << "\"name\":\"" << name << "\",";
			m_outputStream << "\"ph\":\"X\",";
			m_outputStream << "\"pid\":0,";
			m_outputStream << "\"tid\":" << result.threadID << ",";
			m_outputStream << "\"ts\":" << result.start.count();
			m_outputStream << "}";

			m_outputStream.flush();
		}

		void writeHeader() {
			m_outputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_outputStream.flush();
		}

		void writeFooter() {
			m_outputStream << "]}";
			m_outputStream.flush();
		}

		static Instrumentor& get() {
			static Instrumentor instance;
			return instance;
		}
	};

	class InstrumentationTimer {
	public:
		InstrumentationTimer(const char* name) : m_name(name), m_stopped(false) {
			m_startTimepoint = std::chrono::steady_clock::now();
		}

		~InstrumentationTimer() {
			if (!m_stopped)
				stop();
		}

		void stop() {
			auto endTimepoint = std::chrono::steady_clock::now();

			auto highResStart = FloatingPointMicroseconds{ m_startTimepoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch();			std::thread::id id = std::this_thread::get_id();

			Instrumentor::get().writeProfile({ m_name, highResStart, elapsedTime, id });

			m_stopped = true;
		}
	private:
		const char* m_name;
		std::chrono::time_point<std::chrono::steady_clock> m_startTimepoint;
		bool m_stopped;
	};
}

#define DM_PROFILE 1
#if DM_PROFILE
	#define DM_PROFILE_BEGIN_SESSION(name, filepath) ::Deimos::Instrumentor::get().beginSession(name, filepath)
	#define DM_PROFILE_END_SESSION() ::Deimos::Instrumentor::get().endSession()

	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define DM_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define DM_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
		#define DM_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define DM_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define DM_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define DM_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define DM_FUNC_SIG __func__
	#else
		#define DM_FUNC_SIG "DM_FUNC_SIG unknown!"
	#endif

	#define DM_PROFILE_SCOPE(name) ::Deimos::InstrumentationTimer timer##__LINE__(name);
	#define DM_PROFILE_FUNCTION() DM_PROFILE_SCOPE(DM_FUNC_SIG)
#else
	#define DM_PROFILE_BEGIN_SESSION(name, filepath)
	#define DM_PROFILE_END_SESSION()
	#define DM_PROFILE_SCOPE(name)
	#define DM_PROFILE_FUNCTION()
#endif
