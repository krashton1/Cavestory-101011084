#include "Level.h"
#include "Graphics.h"
#include "Globals.h"

#include "tinyxml2.h"

#include <SDL.h>

#include<sstream>
#include<algorithm>
#include<cmath>


using namespace tinyxml2;

Level::Level()
{

}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics & graphics):
	_mapName(mapName),
	_spawnPoint(spawnPoint),
	_size(Vector2(0,0))
{
	loadMap(mapName, graphics);
}

Level::~Level()
{

}

void Level::update(int elapsedTime)
{

}

void Level::draw(Graphics & graphics)
{
	////Draw the background
	//SDL_Rect sourceRect = { 0,0,64,64 };
	//SDL_Rect destRect;
	//for (int x = 0; x < _size.x/64; x++) {
	//	for (int y = 0; y < _size.y / 64; y++) {
	//		destRect.x = x * 64 * globals::SPRITE_SCALE;
	//		destRect.y = y * 64 * globals::SPRITE_SCALE;
	//		destRect.w = 64 * globals::SPRITE_SCALE;
	//		destRect.h = 64 * globals::SPRITE_SCALE;

	//		graphics.blitSurface(_backgroundTexture, &sourceRect, &destRect);
	//	}
	//}

	for (int i = 0; i < _tileList.size(); i++) {
		_tileList.at(i).draw(graphics);
	}
}

void Level::loadMap(std::string mapName, Graphics & graphics)
{
	////TEMP CODE TO LOAD BACKGROUND
	//_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/backgrounds/bkBlue.png"));
	//_size = Vector2(1280, 960);

	//Pase .tmx file
	XMLDocument doc;
	std::stringstream ss;
	ss << "content/maps/" << mapName << ".tmx"; //Pass in Map 1, we get maps/Map 1.tmx
	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");

	//get the width and height of whole map and store it in _zise
	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	_size = Vector2(width, height);

	//get width and height of tiles and store in _tilesize
	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tileWidth", &tileWidth);
	mapNode->QueryIntAttribute("tileHeight", &tileHeight);
	_tileSize = Vector2(tileWidth, tileHeight);

	//Load the tilesets
	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != NULL) {
		while (pTileset) {
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");
			char* path;
			std::stringstream ss;
			ss << "content/tilesets/" << source;
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
			_tilesets.push_back(Tileset(tex, firstgid));

			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	//load the layers
	XMLElement* pLayer= mapNode->FirstChildElement("layer");
	if (pLayer != NULL) {
		while (pLayer) {
			//loading the data element
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != NULL) {
				while (pData) {
					//loading the tile element
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL) {
						int tileCounter = 0;
						while (pTile) {
							//build each individual tile here
							//if gid is 0, no tile is drawn. continue loop
							if (pTile->IntAttribute("gid") == 0) {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							//get the tile set for the specific gid
							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							for (int i = 0; i < _tilesets.size(); i++) {
								if (_tilesets[i].FirstGid<=gid) {
									//this is the tileset we want
									tls=_tilesets.at(i);
									break;
								}
							}

							if (tls.FirstGid == -1) {
								//no tileset was found for this gid
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							//get the position of the tile in the level
							int xx = 0;
							int yy = 0;
							xx = tileCounter%width;
							xx *= tileWidth;
							yy += tileHeight*(tileCounter / width);
							Vector2 finalTilePosition = Vector2(xx, yy);

							//Calc the position of the tile in the tile set
							int tileSetWidth, tileSetHeight;
							SDL_QueryTexture(tls.Texture, NULL, NULL, &tileSetWidth, &tileSetHeight);
							int tsxx = gid % (tileSetWidth / tileWidth) - 1;
							tsxx *= tileWidth;
							int tsyy = 0;
							int amt = (gid / (tileSetWidth / tileWidth));
							tsyy = tileHeight*amt;
							Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);

							//build the actual tile and add it to levels tile list
							//Tile tile(tls.Texture, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
							Tile tile(tls.Texture, Vector2(tileWidth, tileHeight),
								finalTilesetPosition, finalTilePosition);
							_tileList.push_back(tile);
							tileCounter++;

							pTile = pTile->NextSiblingElement("tile");
						}
					}

					pData = pData->NextSiblingElement("data");
					
				}
			}
			pLayer = pLayer->NextSiblingElement("layer");
		}
	}
}
