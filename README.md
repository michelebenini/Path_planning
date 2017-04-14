# Path_planning
Method for path planning
I create a simple mathod for path planning algorithm in c++.

This algorithm simulates the robot's steps. It tries to approach from Start to Goal starting from y and then x.  Because of the presence of the obstacles, it tries to move on a random direction among those possibles, trying not to go back. 
If it finds an hole, it must come back. Before that, it inserts some obstacles on map to plug the hole. In this case, if we reuse the map, we already know that these dots are a trap. Once it finds the path from Start to Goal, the algorithm tries to semplify and reduces the total steps.
So we get a safe path that leads us surely to the goal. This algorithm finds a path but it is not sure it's the optimal path, we reuse the algorthm replacing the Start with Goal and the goal with start and it could choose the path with minor steps.
This algorithm finds a safe path from Start to Goal quickly although in some cases you may not find the best way.
