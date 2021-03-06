#include "Graphics.h"

Graphics::Graphics(int width, int height, const char *title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING)) throw std::string ("Failed to init SDL! SDL Error: ") + SDL_GetError();

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

	mainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,	width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	
	renderer = SDL_CreateRenderer(mainWindow, -1, 0);

	if (TTF_Init()) throw std::string ("Failed to init SDL_ttf! SDL_ttf Error: ") + TTF_GetError() + SDL_GetError();
	font=TTF_OpenFont("fonts/a_OldTyper.ttf",24);
	if( font == NULL ) throw std::string("Failed to load font! SDL_ttf Error: ") + TTF_GetError();
}

Graphics::~Graphics(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(mainWindow);
	TTF_Quit();
	SDL_Quit();
}

Image* Graphics::NewImage(char* file, int r, int g, int b)
{
	SDL_Surface* tmp = IMG_Load(file);
	if (tmp==NULL) throw std::string ("File \"") + file + "\" is not found or broken"; 
	Image* image = new Image();
	if (r>=0) SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, r, g, b));
	image->texture = SDL_CreateTextureFromSurface(renderer, tmp);
	image->h=tmp->h;
	image->w=tmp->w;
	SDL_FreeSurface(tmp);
	return image;
}

Image* Graphics::NewImage(std::wstring &text, SDL_Color &color, bool fast){
	std::basic_string<Uint16> utext (text.begin(),text.end());
	SDL_Surface* tmp = fast ? TTF_RenderUNICODE_Solid(font, utext.c_str(), color) : TTF_RenderUNICODE_Blended(font, utext.c_str(), color);
	if( tmp == NULL ) std::cout << std::endl << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError();
	Image* image = new Image();
	image->texture = SDL_CreateTextureFromSurface(renderer, tmp);
	image->h=tmp->h;
	image->w=tmp->w;
	SDL_FreeSurface(tmp);
	return image;
}

bool Graphics::DrawImage(Image* img, int x, int y)
{
	if(mainWindow == NULL || img->texture == NULL)
		return false;

	SDL_Rect Area;
	Area.x = x;
	Area.y = y;

	Area.w = img->w;
	Area.h = img->h;
	SDL_RenderCopy(renderer, img->texture, NULL, &Area);
	return true;
}

bool Graphics::DrawImage(Image* img, int x, int y, int startX, int startY, int srcW, int srcH, int w, int h)
{
	if(mainWindow == NULL || img->texture == NULL)
		return false;

	SDL_Rect Area;
	Area.x = x;
	Area.y = y;
	Area.w = w;
	Area.h = h;

	SDL_Rect SrcArea;
	SrcArea.x = startX;
	SrcArea.y = startY;
	SrcArea.w = srcW;
	SrcArea.h = srcH;

	SDL_RenderCopy(renderer, img->texture, &SrcArea, &Area);
	return true;
}
bool Graphics::DrawImage(Image* img, int x, int y, int startX, int startY, int srcW, int srcH, double scale) 
{
#pragma warning( push )
#pragma warning( disable : 4244 )
	int w = static_cast<double>(srcW)*scale;
	int h = static_cast<double>(srcH)*scale;
#pragma warning( pop)
	return DrawImage(img,x,y,startX,startY,srcW,srcH,w,h);
}

void Graphics::DestroyImage(Image* image){
	SDL_DestroyTexture(image->texture);
}

void Graphics::SetResolution(int w, int h){
	SDL_SetWindowSize(mainWindow, w, h);
}

void Graphics::Flip()
{
	SDL_SetRenderDrawColor(renderer, 244, 244, 244, 255);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}