#include <GLFW/glfw3.h>
#include <vector>

#define Black 0.0, 0.0, 0.0
#define Red 1.0, 0.0, 0.0
#define Window 800, 600, "OpenGL Lab", NULL, NULL
#define ORTHO_PARAMS -10.0, 10.0, -5.0, 8.0, -1.0, 1.0
#define CLEAR_COLOR_PARAMS 1.0f, 1.0f, 1.0f, 1.0f

class Point { //Використання ООП (розроблення власних класів)
public:
    Point(float x, float y) : x(x), y(y) {}

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    ~Point() {}

private:
    float x, y;
};

class Points { //Використання ООП (розроблення власних класів)
public:
    Points(const std::vector<Point>& points) : points(points) {}

    const std::vector<Point>& getAllCoordinates() const {
        return points;
    }

    ~Points() {}

private:
    std::vector<Point> points;
};

class Figure { //Використання ООП (розроблення власних класів)
public:
    Figure(Points points) : lineWidth(2.0), lineType(GL_LINE_LOOP) {
        for (auto& item : points.getAllCoordinates()) { //Застосування циклів для створення зображень
            vertices.push_back(item.getX());
            vertices.push_back(item.getY());

            separatePoints.push_back(item.getX() + 10.0);
            separatePoints.push_back(item.getY());
        }
    }

    void draw() {
        glLineWidth(lineWidth);
        glLineStipple(1, 0xAAAA); // Пунктирні лінії
        glEnable(GL_LINE_STIPPLE);

        // Виведення фігури
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertices.data());
        glColor3f(Red); // Використання команд управління параметрами графічних примітивів
        glDrawArrays(lineType, 0, vertices.size() / 2); //Формування зображення векторними командами OpenGL (glDrawArrays и т. п.)
        glDisableClientState(GL_VERTEX_ARRAY);

        // Виведення окремих точок
        glPointSize(5.0); // Використання команд управління параметрами графічних примітивів
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, separatePoints.data());
        glColor3f(Black); // Використання команд управління параметрами графічних примітивів
        glDrawArrays(GL_POINTS, 0, separatePoints.size() / 2); //Формування зображення векторними командами OpenGL (glDrawArrays и т. п.)
        glDisableClientState(GL_VERTEX_ARRAY);

        // Виведення осей X та Y
        glLineWidth(1.0);
        glBegin(GL_LINES);
        glColor3f(Black); // Чорний колір для осей
        glVertex2f(-10.0, 0.0);
        glVertex2f(10.0, 0.0);
        glVertex2f(0.0, -5.0);
        glVertex2f(0.0, 8.0);
        glEnd();

        glDisable(GL_LINE_STIPPLE);
    }

    ~Figure() {}

private:
    std::vector<float> vertices;
    std::vector<float> separatePoints;
    float lineWidth;
    GLenum lineType;
};

void display(GLFWwindow* window, Figure& figure) { //Розроблення підпрограм для виключення дублювання коду
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height); // Коректне відображення завдання під час змінення розмірів/положення вікна
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(ORTHO_PARAMS);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(CLEAR_COLOR_PARAMS);
    glClear(GL_COLOR_BUFFER_BIT);

    figure.draw();

    glfwSwapBuffers(window);
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(Window);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    std::vector<Point> points({
        Point(-6.0, 6.0),
        Point(-4.0, 6.0),
        Point(-2.0, 4.0),
        Point(-4.0, 0.0),
        Point(-6.0, -2.0),
        Point(-8.0, 4.0)
        });

    Points pointContainer(points);
    Figure figure(pointContainer);

    while (!glfwWindowShouldClose(window)) {
        display(window, figure);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
