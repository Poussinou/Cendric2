#include "global.h"
#include "Game.h"
#include "ResourceManager.h"
#include "InputController.h"
#include "Logger.h"
#include "TextProvider.h"

sf::RenderTexture *g_renderTexture;

int main(int argc, char* argv[])
{
	g_logger = new Logger();
	g_resourceManager = new ResourceManager();
	g_resourceManager->init();
	g_textProvider = new TextProvider();
	g_textProvider->reload();
	g_inputController = new InputController();
	g_inputController->init();
	g_renderTexture = new sf::RenderTexture();
	g_renderTexture->create(WINDOW_WIDTH, WINDOW_HEIGHT);

	Game* game = new Game();
	game->run();
	delete game;

	delete g_resourceManager;
	delete g_inputController;
	delete g_textProvider;
	delete g_logger;

	return 0;
}