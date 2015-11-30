#ifndef TESTMODULE_HPP
#define TESTMODULE_HPP

#include "Rectangle.hpp"
#include "Action.hpp"
#include "SDL2TK/Module.hpp"
#include "SDL2TK/Matrix4x4.hpp"
#include "SDL2TK/OpenGL/ShaderProgram.hpp"
#include "SDL2TK/Surface.hpp"
#include <vector>
#include <unordered_map>

class TestModule : public SDL2TK::Module
{
    public:
        TestModule();
        virtual ~TestModule();

        virtual void OnOpen();
        virtual void OnClose();
        virtual void OnLoop();
        virtual void OnPulse();
        virtual void OnSecond(int framesPerSecond);

        virtual void OnKeyDown(const SDL_Keysym& keysym);
        virtual void OnKeyUp(const SDL_Keysym& keysym);
        virtual void OnResize(int width, int height);

        virtual void OnControllerAxis(
            const SDL_ControllerAxisEvent& event);
        virtual void OnControllerButtonDown(
            const SDL_ControllerButtonEvent& event);
        virtual void OnControllerButtonUp(
            const SDL_ControllerButtonEvent& event);

    protected:
    private:
        int _pulseCount = 0;

        std::unordered_map<SDL_Keycode, Action<TestModule>> _onKeyDown;
        std::unordered_map<SDL_Keycode, Action<TestModule>> _onKeyUp;

        std::unordered_map<Uint8, Action<TestModule>> _onControllerButtonUp;
        std::unordered_map<Uint8, Action<TestModule>> _onControllerButtonDown;


        SDL2TK::ShaderProgram _simpleProgram;
        GLint _simplePositionAttribute;
        GLint _textureCoordinatesAttribute;
        GLint _textureUniform;

        SDL2TK::ShaderProgram _debugProgram;
        GLint _debugPositionAttribute;
        GLint _colorAttribute;

        GLuint _texture;

        SDL2TK::Matrix4x4F _viewMatrix;
        SDL2TK::Matrix4x4F _playerMatrix;
        SDL2TK::Matrix4x4F _terrainMatrix;
        SDL2TK::RotationF _rotation;

        void LoadSimpleShaders();
        void LoadDebugShaders();
};

#endif
