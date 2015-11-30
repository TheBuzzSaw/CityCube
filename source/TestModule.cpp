#include "TestModule.hpp"
#include "SDL2TK/Tools.hpp"
#include <iostream>
using namespace std;

TestModule::TestModule()
{
    LoadSimpleShaders();
    LoadDebugShaders();

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

    const GLenum params[] = {

        GL_TEXTURE_WRAP_S, GL_REPEAT,
        GL_TEXTURE_WRAP_T, GL_REPEAT,
        GL_TEXTURE_MAG_FILTER, GL_LINEAR,
        GL_TEXTURE_MIN_FILTER, GL_LINEAR,
        0 };

    SDL2TK::Surface("hi.png").LoadIntoTexture(GL_TEXTURE_2D);

    for (int i = 0; params[i]; i += 2)
        glTexParameteri(GL_TEXTURE_2D, params[i], params[i + 1]);

    glDisable(GL_TEXTURE_2D);
}

TestModule::~TestModule()
{
    glDeleteTextures(1, &_texture);
}

void TestModule::OnOpen()
{
    glLineWidth(16.0f);
    glClearColor(0.25f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE0);

    _simpleProgram.Use();
    glUniform1i(_textureUniform, 0);

    glMatrixMode(GL_MODELVIEW);
}

void TestModule::OnClose()
{
    glDisable(GL_BLEND);
    //glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
}

void TestModule::OnLoop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    constexpr float N = 1.0f;

    const float PlayerData[] = {
        -N, -N, 0.0f, 0.0f, 2.0f,
        -N, N, 0.0f, 0.0f, 0.0f,
        N, N, 0.0f, 2.0f, 0.0f,
        N, -N, 0.0f, 2.0f, 2.0f
        };

    _simpleProgram.Use();
    glEnableVertexAttribArray(_simplePositionAttribute);
    glEnableVertexAttribArray(_textureCoordinatesAttribute);

    glBindTexture(GL_TEXTURE_2D, _texture);
    glLoadMatrixf(_viewMatrix * _playerMatrix);

    glVertexAttribPointer(
        _simplePositionAttribute,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(GLfloat) * 5,
        PlayerData);

    glVertexAttribPointer(
        _textureCoordinatesAttribute,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(GLfloat) * 5,
        PlayerData + 3);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableVertexAttribArray(_textureCoordinatesAttribute);
    glDisableVertexAttribArray(_simplePositionAttribute);
}

void TestModule::OnPulse()
{
    ++_pulseCount;

    _rotation += SDL2TK::RotationF::FromDegrees(3.0f);
    _playerMatrix
        .LoadIdentity();

    _viewMatrix
        .LoadIdentity();
}

void TestModule::OnSecond(int framesPerSecond)
{
    return;
    cout
        << framesPerSecond << " frames, "
        << _pulseCount << " pulses"
        << endl;

    _pulseCount = 0;
}

void TestModule::OnKeyDown(const SDL_Keysym& keysym)
{
    if (keysym.sym == SDLK_ESCAPE) Stop();
    SafeCall(_onKeyDown[keysym.sym]);
}

void TestModule::OnKeyUp(const SDL_Keysym& keysym)
{
    SafeCall(_onKeyUp[keysym.sym]);
}

void TestModule::OnControllerAxis(const SDL_ControllerAxisEvent& event)
{

}

void TestModule::OnControllerButtonDown(const SDL_ControllerButtonEvent& event)
{
    SafeCall(_onControllerButtonDown[event.button]);
}

void TestModule::OnControllerButtonUp (const SDL_ControllerButtonEvent& event)
{
    SafeCall(_onControllerButtonUp[event.button]);
}

void TestModule::OnResize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    SDL2TK::Matrix4x4F matrix;
    matrix.Orthographic(1.0f, float(width) / float(height));

    glLoadMatrixf(matrix);
    glMatrixMode(GL_MODELVIEW);
}

void TestModule::LoadSimpleShaders()
{
    _simpleProgram = SDL2TK::ShaderProgram::FromFiles(
        "simple.vertex.shader", "simple.fragment.shader");

    _simplePositionAttribute = _simpleProgram.GetAttributeLocation("position");
    _textureCoordinatesAttribute =
        _simpleProgram.GetAttributeLocation("textureCoordinates");
    _textureUniform = _simpleProgram.GetUniformLocation("theTexture");
}

void TestModule::LoadDebugShaders()
{
    _debugProgram = SDL2TK::ShaderProgram::FromFiles(
        "debug.vertex.shader", "debug.fragment.shader");

    _debugPositionAttribute = _debugProgram.GetAttributeLocation("position");
    _colorAttribute =
        _debugProgram.GetAttributeLocation("color");
}
