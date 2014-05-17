#include "App.hpp"
#include "Game.hpp"

int App::main(const std::vector<std::string>& args)
{
	clan::CrashReporter::hook_thread();

	try
	{
		Game game;
		game.start();
	}
	catch(clan::Exception e)
	{
		clan::ExceptionDialog::show(e);
	}

	return 0;
}