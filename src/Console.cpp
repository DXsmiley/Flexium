#include <Flexium/Console.hpp>
#include <Flexium/Text.hpp>
#include <Flexium/Input.hpp>
#include <Flexium/World.hpp>

#include <map>

namespace flx {

	const char * help_text[] = {
		"Flexium In-Game Console",
		"",
		"	Keyboard shortcuts:",
		"		~ - enable or disable debug mode",
		"		return - begin typing a command",
		"",
		"	Inbuilt commands:",
		"		help - show this help",
		"		info - show information about the engine",
		"		clear (cls) - clear the in-game console",
		"   	exit - close the game",
		"   	trigupdate - toggle update event",
		"   	trigdraw - toggle draw event",
		"",
		"#"
	};

	const char * info_text[] = {
		"Flexium Game Engine",
		""
		"	Flexium is a game engine written by DXsmiley",
		"	It is written in C++ and relies on SFML",
		"",
		"#"
	};

	std::map<std::string, void (*)(const Console::CommandInfo&)> command_map;

	void cmdLogClear(const Console::CommandInfo& ci) {
		ci.console -> clear();
	}

	void cmdLogHelp(const Console::CommandInfo&) {
		for (unsigned int i = 0; help_text[i][0] != '#'; i++) {
			Console::Log << help_text[i] << std::endl;
		}
	}

	void cmdLogInfo(const Console::CommandInfo&) {
		for (unsigned int i = 0; info_text[i][0] != '#'; i++) {
			Console::Log << info_text[i] << std::endl;
		}
	}

	void cmdProgEnd(const Console::CommandInfo&) {
		std::cout << "Shutdown" << std::endl;
		Window::close();
	}

	void cmdTriggerUpdate(const Console::CommandInfo& ci) {
		if (ci.world -> getTriggerUpdate()) {
			Console::Log << "Disabled Update Event" << std::endl;
			ci.world -> setTriggerUpdate(false);
		} else {
			Console::Log << "Enabled Update Event" << std::endl;
			ci.world -> setTriggerUpdate(true);
		}
	}

	void cmdTriggerDraw(const Console::CommandInfo& ci) {
		if (ci.world -> getTriggerDraw()) {
			Console::Log << "Disabled Draw Event" << std::endl;
			ci.world -> setTriggerDraw(false);
		} else {
			Console::Log << "Enabled Draw Event" << std::endl;
			ci.world -> setTriggerDraw(true);
		}
	}

	namespace Console {

		void commandSet(std::string name, void (*func)(const Console::CommandInfo&)) {
			command_map[name] = func;
		}

		ConsoleStream Log("L > ");
		ConsoleStream Warn("W > ");
		ConsoleStream Error("E > ");

	};

	void ConsoleStream::setInGameConsole(ConsoleInGame * c) {
		buffer.cig = c;
	}

	int ConsoleStream::MyStreamBuffer::sync() {
		//ConsoleInGame * cig = world -> instanceGetSingle<ConsoleInGame*>();
		if (cig != NULL) cig -> addLine(prefix + str());
		std::cout << prefix << str();
		str("");
		std::cout.flush();
		return 0;
	}

	void ConsoleInGame::addLine(std::string s) {
		//std::cout << "added Line: " << s << std::endl;
		lines.push_back(s);
		if (lines.size() > 20) lines.pop_front();
	}

	void ConsoleInGame::clear() {
		lines.clear();
	}

	void ConsoleInGame::onCreate() {
		// Should probably not have this hard coded, in case people want multiple in-game consoles.
		Console::Log.setInGameConsole(this);
		Console::Warn.setInGameConsole(this);
		Console::Error.setInGameConsole(this);
		setDepth(1);
		setMeta(true);
		Console::commandSet("help", cmdLogHelp);
		Console::commandSet("?", cmdLogHelp);
		Console::commandSet("info", cmdLogInfo);
		Console::commandSet("clear", cmdLogClear);
		Console::commandSet("cls", cmdLogClear);
		Console::commandSet("exit", cmdProgEnd);
		Console::commandSet("trigupdate", cmdTriggerUpdate);
		Console::commandSet("trigdraw", cmdTriggerDraw);
		setPersistent(true);
	}

	void ConsoleInGame::onUpdate() {
		if (!debug) {
			typing = false;
			command = "";
		} else {
			if (Input::keyPressed(Input::Key::Return)) {
				if (typing) {
					std::vector<std::string> vec;
					std::stringstream ss;
					ss << command;
					while (true) {
						std::string arg = "";
						ss >> arg;
						if (arg == "") break;
						vec.push_back(arg);
					}
					if (!vec.empty()) {
						void (*func)(const Console::CommandInfo&) = command_map[vec[0]];
						if (func != NULL) {
							Console::CommandInfo ci;
							ci.args = std::vector<std::string>(std::next(vec.begin()), vec.end());
							ci.world = getWorld();
							ci.console = this;
							(*func)(ci);
						} else {
							Console::Error << "No command named '" << vec[0] << "'" << std::endl;
						}
					}
					command = "";
				}
				typing = !typing;		
			}
			char c = Input::characterTyped();
			if (typing && c != '\0') {
				switch (c) {
					case '\b':
						if (command.size() > 0) {
							command.pop_back();
						}
						break;
					case '\r':
					case '\n':
						break;
					default:
						command += c;
						break;
				}
			}
		}
	}

	void ConsoleInGame::onDraw() {
		static ::sf::Clock fps_clock;
		static int tick_counter = 30;
		static double fps_hold = 0;
		double fps = 1.0f / std::max((float)(1.0 / 512.0), fps_clock.restart().asSeconds()); // std::max prevents division by zero
		if (--tick_counter == 0) {
			tick_counter = 30;
			fps_hold = fps;
		}
		if (debug) {
			Window::viewSetZoom(1);
			Window::viewSetPositionZero();
			std::stringstream ss;
			ss << "FPS: " << fps << ", " << fps_hold;
			Text::draw(20, 20, ss.str(), "console", 12, sf::Color::Green);
			int y = 36;
			for (auto i: lines) {
				sf::Color col = sf::Color::White;
				if (i[0] == 'L') col = sf::Color::Cyan;
				if (i[0] == 'W') col = sf::Color::Yellow;
				if (i[0] == 'E') col = sf::Color::Red;
				Text::draw(20, y += 16, i, "console", 12, col);
			}
			if (typing) Text::draw(20, y + 32, std::string(">>> ") + command, "console", 12, sf::Color::Green);
		}
	}

}