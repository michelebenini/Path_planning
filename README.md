# Path_planning
Method for path planning
I create a simple mathod for path planning algorithm in c++.

This algorithm simulates the robot's steps, it try to approach from Start to Goal, before it try towards y and after towards x. If it can't do so because of the presence of obstacles it try to move on a random direction among those possible trying to not go back. 
If it find an hole it must come back, before to do that, it insert some obstacles on map to plug the hole, in this case if we must reuse the map we already know that this dots are a trap. Once it find the path from Start to Goal the algorithm try to semplify, if it possible, and reduce the total steps.
So we get a safe path that leads us surely to the goal. This algorithm find a path but is not sure it's the optimal path, we reuse the algorthm replacing the Start with Goal and the goal with start and it must chose the path with minor steps.
This algorithm find a safe path from Start to Goal quickly although in some cases you may not find the best way.
