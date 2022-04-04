#pragma once
#include <map>
#include <string>
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_image.h>

class LTexture{
private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    void* mPixels;
    int mPitch;

    //Image dimensions
    int mWidth;
    int mHeight;
public:
    //Initializes variables
    LTexture(){
        //Initialize
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
        mPixels = NULL;
        mPitch = 0;
    }

    //Deallocates memory
    ~LTexture() {
        //Deallocate
        free();
    }

    //Loads image at specified path
    bool loadFromFile(std::string path, SDL_Window* Window, SDL_Renderer* Renderer) {
        //Get rid of preexisting texture
        free();

        //The final texture
        SDL_Texture* newTexture = NULL;

        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        }
        else
        {
            //Convert surface to display format
            SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(Window), 0);
            if (formattedSurface == NULL)
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
            }
            else
            {
                //Create blank streamable texture
                newTexture = SDL_CreateTexture(Renderer, SDL_GetWindowPixelFormat(Window), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
                if (newTexture == NULL)
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
                }
                else
                {
                    //Lock texture for manipulation
                    SDL_LockTexture(newTexture, NULL, &mPixels, &mPitch);

                    //Copy loaded/formatted surface pixels
                    memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

                    //Unlock texture to update
                    SDL_UnlockTexture(newTexture);
                    mPixels = NULL;

                    //Get image dimensions
                    mWidth = formattedSurface->w;
                    mHeight = formattedSurface->h;
                }

                //Get rid of old formatted surface
                SDL_FreeSurface(formattedSurface);
            }

            //Get rid of old loaded surface
            SDL_FreeSurface(loadedSurface);
        }

        //Return success
        mTexture = newTexture;
        if (mTexture == NULL) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Fail to load Player texture");
        }
        return mTexture != NULL;
    }

#if defined(SDL_TTF_MAJOR_VERSION)
    //Creates image from font string
    bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
    {
        //Get rid of preexisting texture
        free();

        //Render text surface
        SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
        if (textSurface != NULL)
        {
            //Create texture from surface pixels
            mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
            if (mTexture == NULL)
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            }
            else
            {
                //Get image dimensions
                mWidth = textSurface->w;
                mHeight = textSurface->h;
            }

            //Get rid of old surface
            SDL_FreeSurface(textSurface);
        }
        else
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        }


        //Return success
        return mTexture != NULL;
    }
#endif

    
    void free() {
        //Free texture if it exists
        if (mTexture != NULL)
        {
            SDL_DestroyTexture(mTexture);
            mTexture = NULL;
            mWidth = 0;
            mHeight = 0;
            mPixels = NULL;
            mPitch = 0;
        }
    }

    void setColor(Uint8 red, Uint8 green, Uint8 blue) {
        //Modulate texture rgb
        SDL_SetTextureColorMod(mTexture, red, green, blue);
    }

    //Set blending
    void setBlendMode(SDL_BlendMode blending) {
        //Set blending function
        SDL_SetTextureBlendMode(mTexture, blending);
    }

    //Set alpha modulation
    void setAlpha(Uint8 alpha) {
        //Modulate texture alpha
        SDL_SetTextureAlphaMod(mTexture, alpha);
    }

    //Renders texture at given point
    void render(SDL_Renderer* Renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE){
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { x, y, mWidth, mHeight };

        //Set clip rendering dimensions
        if (clip != NULL)
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        //Render to screen
        //SDL_RenderCopyEx(Renderer, mTexture, clip, &renderQuad, angle, center, flip);
        SDL_RenderCopy(Renderer, mTexture, NULL, &renderQuad);
    }

    //Gets image dimensions
    int getWidth() {
        return mWidth;
    }
    int getHeight() {
        return mHeight;
    }

    //Pixel manipulators
    bool lockTexture() {
        bool success = true;

        //Texture is already locked
        if (mPixels != NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Texture is already locked!\n");
            success = false;
        }
        //Lock texture
        else
        {
            if (SDL_LockTexture(mTexture, NULL, &mPixels, &mPitch) != 0)
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Unable to lock texture! %s\n", SDL_GetError());
                success = false;
            }
        }

        return success;
    }
    bool unlockTexture() {
        bool success = true;

        //Texture is not locked
        if (mPixels == NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Texture is not locked!\n");
            success = false;
        }
        //Unlock texture
        else
        {
            SDL_UnlockTexture(mTexture);
            mPixels = NULL;
            mPitch = 0;
        }

        return success;
    }
    void* getPixels() {
        return mPixels;
    }
    int getPitch() {
        return mPitch;
    }


};



