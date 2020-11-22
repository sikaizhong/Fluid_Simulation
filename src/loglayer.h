#ifndef LOGLAYER_
#define LOGLAYER_
#include<spdlog/spdlog.h>
#include<spdlog/fmt/ostr.h>
namespace FS {

	/*template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}*/

	class Log
	{
	public:
		static void Init();

		//Create a multiple loggers all sharing the same file (sink) aka categories
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};


#define TB_QT_TRACE(...)    ::FS::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TB_QT_INFO(...)     ::FS::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TB_QT_WARN(...)     ::FS::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TB_QT_ERROR(...)    ::FS::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TB_QT_CRITICAL(...) ::FS::Log::GetCoreLogger()->critical(__VA_ARGS__)

	// Client log macros
#define TB_RENDER_TRACE(...)         ::FS::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TB_RENDER_INFO(...)          ::FS::Log::GetClientLogger()->info(__VA_ARGS__)
#define TB_RENDER_WARN(...)          ::FS::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TB_RENDER_ERROR(...)         ::FS::Log::GetClientLogger()->error(__VA_ARGS__)
#define TB_RENDER_CRITICAL(...)      ::FS::Log::GetClientLogger()->critical(__VA_ARGS__)
}


#endif 