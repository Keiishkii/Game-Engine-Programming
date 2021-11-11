#include <exception>
#include <string>

namespace Engine
{
	namespace ErrorHandling
	{
		struct Exception : public std::exception
		{
		private:
			std::string _errorMessage;
		public:


		private:
		public:
			Exception(std::string errorMessage);
			~Exception() throw();

			const std::string What();
			void Print();
		};
	}
}