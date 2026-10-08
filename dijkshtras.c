#include <stdio.h>

#define MAX 20
#define INF 99999

int graph[MAX][MAX];
int distance[MAX];
int visited[MAX];
int parent[MAX];
int n;

void enterGraph()
{
    int i, j;

    printf("\nEnter number of locations: ");
    scanf("%d", &n);

    printf("\nEnter the adjacency matrix:\n");
    printf("(Enter 0 for same location and %d for no direct connection)\n\n", INF);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);

            if (i != j && graph[i][j] == 0)
                graph[i][j] = INF;
        }
    }

    printf("\nCampus graph entered successfully.\n");
}

void displayGraph()
{
    int i, j;

    if (n == 0)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }

    printf("\nAdjacency Matrix:\n\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                printf("%6s", "INF");
            else
                printf("%6d", graph[i][j]);
        }
        printf("\n");
    }
}

int selectSource()
{
    int source;

    printf("\nEnter source location number (1-%d): ", n);
    scanf("%d", &source);

    if (source < 1 || source > n)
    {
        printf("Invalid source location.\n");
        return -1;
    }

    return source - 1;
}

void dijkstra(int source)
{
    int i, j;
    int minDistance;
    int current;

    for (i = 0; i < n; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    distance[source] = 0;

    for (i = 0; i < n - 1; i++)
    {
        minDistance = INF;
        current = -1;

        for (j = 0; j < n; j++)
        {
            if (!visited[j] && distance[j] < minDistance)
            {
                minDistance = distance[j];
                current = j;
            }
        }

        if (current == -1)
            break;

        visited[current] = 1;

        for (j = 0; j < n; j++)
        {
            if (!visited[j] &&
                graph[current][j] != INF &&
                distance[current] + graph[current][j] < distance[j])
            {
                distance[j] = distance[current] + graph[current][j];
                parent[j] = current;
            }
        }
    }

    printf("\nShortest distances calculated successfully.\n");
}

void displayPath(int vertex)
{
    if (parent[vertex] == -1)
    {
        printf("%d", vertex + 1);
        return;
    }

    displayPath(parent[vertex]);
    printf(" -> %d", vertex + 1);
}

void displayShortestPaths(int source)
{
    int i;

    printf("\n%-15s %-20s %-30s\n",
           "Destination", "Shortest Distance", "Shortest Path");

    printf("\n");

    for (i = 0; i < n; i++)
    {
        if (i == source)
            continue;

        printf("%-15d ", i + 1);

        if (distance[i] == INF)
        {
            printf("%-20s", "INF");
            printf("No path");
        }
        else
        {
            printf("%-20d", distance[i]);
            displayPath(i);
        }

        printf("\n");
    }
}

void displayDistances(int source)
{
    int i;

    printf("\nDistance from Source Location %d:\n\n", source + 1);

    for (i = 0; i < n; i++)
    {
        if (i == source)
            printf("Location %d -> Source (0)\n", i + 1);
        else if (distance[i] == INF)
            printf("Location %d -> No path\n", i + 1);
        else
            printf("Location %d -> %d\n", i + 1, distance[i]);
    }
}

int main()
{
    int choice;
    int source = -1;
    int graphEntered = 0;
    int shortestPathCalculated = 0;

    n = 0;

    do
    {
        printf("\n============================================");
        printf("\n     CAMPUS SHORTEST ROUTE FINDER");
        printf("\n============================================");
        printf("\n1. Enter Campus Graph");
        printf("\n2. Display Adjacency Matrix");
        printf("\n3. Select Source Location");
        printf("\n4. Find Shortest Distance");
        printf("\n5. Display Shortest Paths");
        printf("\n6. Display Distance from Source to All Locations");
        printf("\n7. Exit");
        printf("\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterGraph();
                graphEntered = 1;
                shortestPathCalculated = 0;
                break;

            case 2:
                displayGraph();
                break;

            case 3:
                if (!graphEntered)
                {
                    printf("\nPlease enter the campus graph first.\n");
                }
                else
                {
                    source = selectSource();

                    if (source != -1)
                    {
                        printf("Source location selected: %d\n", source + 1);
                    }
                }
                break;

            case 4:
                if (!graphEntered)
                {
                    printf("\nPlease enter the campus graph first.\n");
                }
                else if (source == -1)
                {
                    printf("\nPlease select a source location first.\n");
                }
                else
                {
                    dijkstra(source);
                    shortestPathCalculated = 1;
                }
                break;

            case 5:
                if (!shortestPathCalculated)
                {
                    printf("\nPlease find shortest distances first.\n");
                }
                else
                {
                    displayShortestPaths(source);
                }
                break;

            case 6:
                if (!shortestPathCalculated)
                {
                    printf("\nPlease find shortest distances first.\n");
                }
                else
                {
                    displayDistances(source);
                }
                break;

            case 7:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice! Please enter 1-7.\n");
        }

    } while (choice != 7);

    return 0;
}
