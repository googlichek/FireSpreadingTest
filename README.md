This is a simple simulation of fire spreading across the scene, where wind speed and direction affect the simulation.

I've tried to approach this project not as a prototype, but as something I would try to write in production. So the project is a bit heavy on some boilerplate, because I like overriding default Gameplay Framework classes in case I may need to do something extra, which happens almost every time.

Also while implementing fire spread functionality I realized that I could've looked into a spatial grid instead of relying on area overlaps, but I was already constrained by the time I figured that out.

I didn't spend too much effort on the Debug UI, and because of that there is some area for improvement (to avoid excessive code duplication, for instance), but I think it serves its purpose as a debug tool pretty well.

I've also added an Arrow Component to make it easier to track the direction and speed of wind.

For performance tricks: I use Environment Queries to determine cube spawn positions. I also don't like doing stuff every frame, which is why I don't try to burn overlapping cubes every frame or update colors in dynamic materials constantly. Again, I think utilizing a spatial grid would've been better performance-wise, but I decided not to risk not shipping anything at all.
