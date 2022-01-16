#include <exception>
#include <string>

namespace Engine
{
	namespace ErrorHandling
	{
		/**	The Exception class used to perform error handling from within the engine and game.  	*/
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