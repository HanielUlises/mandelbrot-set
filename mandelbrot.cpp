#include "mandelbrot.h"

// Constructor for the Mandelbrot class
mandelbrot::mandelbrot() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }

    // Adjust the window size and coordinates for a better view of the Mandelbrot set
    window = SDL_CreateWindow(
        "Mandelbrot Set",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600, // Changed the height to make it fit nicely
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    // Check if window creation failed
    if (window == nullptr) {
        std::cout << "Failed to create a window <<SDL_Window>>" << std::endl;
        return;
    }

    // Create an SDL renderer with hardware acceleration
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    // Check if renderer creation failed
    if (renderer == nullptr) {
        std::cout << "Failed to create a renderer <<SDL_Renderer>> " << std::endl;
        return;
    }

    // Initialize the flag for the main loop
    isRunning = true;
}

// Destructor for the Mandelbrot class
mandelbrot::~mandelbrot() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Function to display the Mandelbrot set
void mandelbrot::display() {
    // Define the view parameters for the Mandelbrot set
    double minX = -2.0;
    double maxX = 1.0;
    double minY = -1.5; // Adjusted to center the Mandelbrot set
    double maxY = 1.5;  // Adjusted to center the Mandelbrot set

    while (isRunning) {
        // Handle SDL events
        handleEvents();

        // Adjust the iteration steps for smoother rendering
        for (double i = 0.0; i < 1.0; i += 0.002) {
            for (double j = 0.0; j < 1.0; j += 0.002) {
                double point_X = std::lerp(minX, maxX, i);
                double point_Y = std::lerp(minY, maxY, j);

                int iter = isInSet(std::complex<double>(point_X, point_Y));

                if (iter == 0) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                }
                else {
                    SDL_SetRenderDrawColor(renderer, 255 - iter, 255 - iter, 255 - iter, 255);
                }

                // Map screen coordinates based on the window size
                int x = static_cast<int>((point_X - minX) / (maxX - minX) * 800);
                int y = static_cast<int>((point_Y - minY) / (maxY - minY) * 600);

                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        // Update the renderer
        SDL_RenderPresent(renderer);
    }
}

// Function to determine if a complex number is in the Mandelbrot set
int mandelbrot::isInSet(std::complex<double> c) {
    std::complex<double> z(0, 0);

    for (int i = 0; i < 256; i++) { // Increased the number of iterations for better accuracy
        z = std::pow(z, 2) + c;

        if (std::norm(z) > 4.0) {
            return i;
        }
    }

    return 0;
}

// Function to handle SDL events
void mandelbrot::handleEvents() {
    SDL_Event ev;

    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_WINDOWEVENT) {
            if (ev.window.event == SDL_WINDOWEVENT_CLOSE)
                isRunning = false;
        }
        if (ev.type == SDL_KEYDOWN) {
            if (ev.key.keysym.sym == SDLK_ESCAPE)
                isRunning = false;
        }
    }
}
