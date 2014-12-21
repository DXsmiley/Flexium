#include "Console.hpp"
#include "Text.hpp"
#include "Input.hpp"

#include <map>

const char * help_text[] = {
	"Flexium In-Game Console",
	"",
	"Keyboard shortcuts:",
	"	~ - enable or disable debug mode",
	"	return - begin typing a command",
	"",
	"Inbuilt commands:",
	"	help - show this help",
	"	clear (cls) - clear the in-game console:",
	"   exit - close the game",
	"",
	"#"
};

std::map<std::string, void (*)(std::vector<std::string>) > command_map;

void cmdLogClear(std::vector<std::string>) {
	// This doesn't work D:
}

void cmdLogHelp(std::vector<std::string>) {
	for (unsigned int i = 0; help_text[i][0] != '#'; i++) {
		Console::Log << help_text[i] << std::endl;
	}
}

void cmdProgEnd(std::vector<std::string>) {
	std::cout << "Shutdown" << std::endl;
	Window::close();
}

namespace Console {

	void commandSet(std::string name, void (*func)(std::vector<std::string>)) {
		command_map[name] = func;
	}

	ConsoleStream Log("L > ");
	ConsoleStream Warn("W > ");
	ConsoleStream Error("E > ");

};

void ConsoleStream::setInGameConsole(ConsoleInGame * c) {
	buffer.cig = c;
}

void ConsoleInGame::addLine(std::string s) {
	//std::cout << "added Line: " << s << std::endl;
	lines.push_back(s);
	if (lines.size() > 20) lines.pop_front();
}

void ConsoleInGame::onCreate() {
	setDepth(1);
	Console::commandSet("help", cmdLogHelp);
	Console::commandSet("?", cmdLogHelp);
	Console::commandSet("clear", cmdLogClear);
	Console::commandSet("cls", cmdLogClear);
	Console::commandSet("exit", cmdProgEnd);
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
					void (*func)(std::vector<std::string>) = command_map[vec[0]];
					if (func != NULL) {
						std::vector<std::string> args(std::next(vec.begin()), vec.end());
						(*func)(args);
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
	static sf::Clock fps_clock;
	static int tick_counter = 30;
	static double fps_hold = 0;
	double fps = 1.0f / std::max((float)(1.0 / 512.0), fps_clock.restart().asSeconds()); // std::max prevents  division by zero
	if (--tick_counter == 0) {
		tick_counter = 30;
		fps_hold = fps;
	}
	if (debug) {
		Window::viewSetZoom(1);
		Window::viewSetPositionZero();
		std::stringstream ss;
		ss << "FPS: " << fps << ", " << fps_hold;
		Text::draw(20, 20, ss.str(), "console", 12);
		int y = 36;
		for (auto i: lines) {
			Text::draw(20, y += 16, i, "console", 12);
		}
		if (typing) Text::draw(20, y + 32, std::string(">>> ") + command, "console", 12);
	}
}
