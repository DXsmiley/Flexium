#ifndef INPUT_HPP
#define INPUT_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace flx {

	class Vector;

	/**
		Provides functions for checking the state of input devices, such is the keyboard and mouse.
	*/
	namespace Input {

		/**
			Update the state of the user input and handle window events.
			Must be called exactly once per game tick.
		*/
		void update();

		/**
			Checks if a key is currently being held down.
			@param key code
			@retuns true if the key is held
		*/
		bool keyDown(int);

		/**
			Checks if a key was pressed this tick.
			@param key code
			@returns true if the key was pressed
		*/
		bool keyPressed(int);

		/**
			Checks if a key was released this tick.
			@param key code
			@returns true if the key was pressed
		*/
		bool keyReleased(int);

		/**
			Checks if a key is currently being held down.
			Supports extra special codes for handling modier keys.
			@param key code
			@retuns true if the key is held
		*/
		bool keyDownEx(int);

		/**
			Checks if a key was pressed this tick.
			Supports extra special codes for handling modier keys.
			@param key code
			@returns true if the key was pressed
		*/
		bool keyPressedEx(int);

		/**
			Checks if a key was released this tick.
			Supports extra special codes for handling modier keys.
			@param key code
			@returns true if the key was pressed
		*/
		bool keyReleasedEx(int);

		/**
			Returns the character typed during this game tick.
			If multiple characters are typed, only the last one will be avaliable.
			@returns the character typed or '\0' if no character was typed.
			@warning this value can be special characters such as '\t' or '\n', so be careful.
		*/
		char characterTyped();

		/**
			Check if a mouse button is currently being held.
			@param mouse button id
			@returns true if the button is being pressed, false otherwise.
		*/
		bool mouseDown(int);

		/**
			Check if a mouse button has just been pressed.
			This value will only be true for a single tick after the button is pressed.
			@param mouse button id
		*/
		bool mousePressed(int);

		/**
			Check if a mouse button has just been released.
			This value will only be true for a single tick after the button is released.
			@param mouse button id
		*/
		bool mouseReleased(int);

		/**
			Gets the current position of the mouse cursor, relative to the window.
			@returns the cursor's current position, as a vector
		*/
		Vector mouse();

		/**
			Gets the current x position of the mouse cursor, relative to the window.
			@returns the cursor's x position
		*/
		double mouseX();
		
		/**
			Gets the current x position of the mouse cursor, relative to the window.
			@returns the cursor's x position
		*/
		double mouseY();

		/**
			Enumeration of mouse buttons. Taken from SFML 2.1. Subject to change if SFML does.
		*/
		namespace Button {
			enum {
				Left,
				Right,
				Middle,
				XButton1,
				XButton2,
				ButtonCount
			};
		}

		/**
			Enumeration of keyboard key codes. Taken from SFML 2.1. Subject to change if SFML does.
		*/
		namespace Key {
			enum {
				Unknown = -1, 
				A = 0, 
				B, 
				C, 
				D, 
				E, 
				F, 
				G, 
				H, 
				I, 
				J, 
				K, 
				L, 
				M, 
				N, 
				O, 
				P, 
				Q, 
				R, 
				S, 
				T, 
				U, 
				V, 
				W, 
				X, 
				Y, 
				Z, 
				Num0, 
				Num1, 
				Num2, 
				Num3, 
				Num4, 
				Num5, 
				Num6, 
				Num7, 
				Num8, 
				Num9, 
				Escape, 
				LControl, 
				LShift, 
				LAlt, 
				LSystem, 
				RControl, 
				RShift, 
				RAlt, 
				RSystem, 
				Menu, 
				LBracket, 
				RBracket, 
				SemiColon, 
				Comma, 
				Period, 
				Quote, 
				Slash, 
				BackSlash, 
				Tilde, 
				Equal, 
				Dash, 
				Space, 
				Return, 
				BackSpace, 
				Tab, 
				PageUp, 
				PageDown, 
				End, 
				Home, 
				Insert, 
				Delete, 
				Add, 
				Subtract, 
				Multiply, 
				Divide, 
				Left, 
				Right, 
				Up, 
				Down, 
				Numpad0, 
				Numpad1, 
				Numpad2, 
				Numpad3, 
				Numpad4, 
				Numpad5, 
				Numpad6, 
				Numpad7, 
				Numpad8, 
				Numpad9, 
				F1, 
				F2, 
				F3, 
				F4, 
				F5, 
				F6, 
				F7, 
				F8, 
				F9, 
				F10, 
				F11, 
				F12, 
				F13, 
				F14, 
				F15, 
				Pause, 
				KeyCount,
				ExShift,
				ExControl,
				ExAlt,
				ExSystem,
				ExKeyCount
			};
		}
	};

}

#endif