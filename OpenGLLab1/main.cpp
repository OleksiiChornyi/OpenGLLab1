#include <GLFW/glfw3.h>
#include <vector>

#define Black 0.0, 0.0, 0.0
#define Red 1.0, 0.0, 0.0
#define Window 800, 600, "OpenGL Lab", NULL, NULL
#define ORTHO_PARAMS -10.0, 10.0, -5.0, 8.0, -1.0, 1.0
#define CLEAR_COLOR_PARAMS 1.0f, 1.0f, 1.0f, 1.0f

class Point { //������������ ��� (����������� ������� �����)
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

class Points { //������������ ��� (����������� ������� �����)
public:
    Points(const std::vector<Point>& points) : points(points) {}

    const std::vector<Point>& getAllCoordinates() const {
        return points;
    }

    ~Points() {}

private:
    std::vector<Point> points;
};

class Figure { //������������ ��� (����������� ������� �����)
public:
    Figure(Points points) : lineWidth(2.0), lineType(GL_LINE_LOOP) {
        for (auto& item : points.getAllCoordinates()) { //������������ ����� ��� ��������� ���������
            vertices.push_back(item.getX());
            vertices.push_back(item.getY());

            separatePoints.push_back(item.getX() + 10.0);
            separatePoints.push_back(item.getY());
        }
    }

    void draw() {
        glLineWidth(lineWidth);
        glLineStipple(1, 0xAAAA); // �������� ��
        glEnable(GL_LINE_STIPPLE);

        // ��������� ������
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, vertices.data());
        glColor3f(Red); // ������������ ������ ��������� ����������� ��������� ��������
        glDrawArrays(lineType, 0, vertices.size() / 2); //���������� ���������� ���������� ��������� OpenGL (glDrawArrays � �. �.)
        glDisableClientState(GL_VERTEX_ARRAY);

        // ��������� ������� �����
        glPointSize(5.0); // ������������ ������ ��������� ����������� ��������� ��������
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, separatePoints.data());
        glColor3f(Black); // ������������ ������ ��������� ����������� ��������� ��������
        glDrawArrays(GL_POINTS, 0, separatePoints.size() / 2); //���������� ���������� ���������� ��������� OpenGL (glDrawArrays � �. �.)
        glDisableClientState(GL_VERTEX_ARRAY);

        // ��������� ���� X �� Y
        glLineWidth(1.0);
        glBegin(GL_LINES);
        glColor3f(Black); // ������ ���� ��� ����
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

void display(GLFWwindow* window, Figure& figure) { //����������� ��������� ��� ���������� ���������� ����
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height); // �������� ����������� �������� �� ��� ������� ������/��������� ����
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
