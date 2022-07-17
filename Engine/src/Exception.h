#pragma once

#include <exception>
#include <memory>
#include <string>
#include <regex>
#include <SDL.h>
			 
namespace mp {

	struct MpException : public std::exception {
		using exception::exception;
	};

	struct MpOutOfMemory : public std::exception {
		using exception::exception;
	};

	struct MpGraphicsInitException : public std::exception {
		using exception::exception;
	};

	struct MpGraphicsException : public std::exception {
		using exception::exception;
	};

	/// <summary>
	/// Throws an exception of type T. Setting the message to the value of the message parameter.
	/// </summary>
	/// <typeparam name="T">
	/// The exception type. Should be a subclass of std::exception.
	/// </typeparam>
	/// <param name="message">
	/// Message passed to the exception constructor. The string '_se' will be interpolated to
	/// the value of SDL_GetError();
	/// </param>
	template<typename T>
	void Throw(const std::string& message) {
		static_assert(std::is_base_of<std::exception, T>::value);
		auto newMessage = std::regex_replace(message, std::regex("_se"), SDL_GetError());
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, message.c_str());
		throw new std::exception(newMessage.c_str());
	}

	/// <summary>
	/// Throws an exception of type T when t is null. Setting the message to the value of the message parameter.
	/// </summary>
	/// <typeparam name="T">
	/// The exception type. Should be a subclass of std::exception.
	/// </typeparam>
	/// <param name="t">
	/// Pointer we are going to test against.
	/// </param>
	/// <param name="message">
	/// Message passed to the exception constructor. The string '_se' will be interpolated to
	/// the value of SDL_GetError();
	/// </param>
	template<class T, class P>
	P* ThrowWhenNull(P* t, const std::string& message) {
		if (!t)
			Throw<T>(message);
		return t;
	}

	template<typename E, class T>
	void ThrowWhenNull(const std::unique_ptr<T, std::default_delete<T>>& t, const std::string& message) {
		if (!t)
			Throw<E>(message);
	}

	/// <summary>
	/// Throws an exception of type T when t is NOT 0. Setting the message to the value of the message parameter.
	/// </summary>
	/// <typeparam name="T">
	/// The exception type. Should be a subclass of std::exception.
	/// </typeparam>
	/// <param name="t">
	/// Pointer we are going to test against.
	/// </param>
	/// <param name="message">
	/// Message passed to the exception constructor. The string '_se' will be interpolated to
	/// the value of SDL_GetError();
	/// </param>
	template<typename T>
	void ThrowWhenNotZero(int t, const std::string& message) {
		if (t)
			Throw<T>(message);
	}
}
