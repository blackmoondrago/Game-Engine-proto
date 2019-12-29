#include "TextureHandler.h"

std::unique_ptr<TextureHandler> TextureHandler::textureInstance = std::unique_ptr<TextureHandler>();
std::map<std::string,Texture*> TextureHandler::textures = std::map<std::string, Texture*>();

TextureHandler* TextureHandler::GetInstance()
{
	if (textureInstance.get() == nullptr)
	{
		textureInstance.reset(new TextureHandler);
	}
	return textureInstance.get();
}

void TextureHandler::CreateTexture(const std::string& textureName_, const std::string& textureFileName_)
{
	Texture* t = new Texture();
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(textureFileName_.c_str());
	//surface = IMG_Load("./Engine/Textures/diceMap.jpg");
	if (!surface)
	{
		Debug::Error("faild to load texture " + textureName_, "textHandler.cpp", __LINE__);
		return;
	}
	t->width = surface->w;
	t->height = surface->h;
	glGenTextures(1, &t->textureID);
	glBindTexture(GL_TEXTURE_2D, t->textureID);
	int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	textures[textureName_] = t;
	SDL_FreeSurface(surface);
	surface = nullptr;
}

const GLuint TextureHandler::GetTexture(const std::string& textureName_)
{
	if (textures.find(textureName_) != textures.end())
	{
		return textures[textureName_]->textureID;
	}
	return 0;
}





const Texture *TextureHandler::GetTextureData(const std::string &TextName_)
{
	if (textures.find(TextName_) != textures.end())
	{
		return textures[TextName_];
	}
	return 0;
}

void TextureHandler::OnDestroy()
{
	if (textures.size() > 0)
	{
		for (auto t : textures)
		{
			glDeleteTextures(sizeof(GLuint), &t.second->textureID);
			delete t.second;
			t.second = nullptr;
		}

		textures.clear();
	}
}

TextureHandler::~TextureHandler()
{
	OnDestroy();
}

TextureHandler::TextureHandler() {

}
