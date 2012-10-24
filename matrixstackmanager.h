#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <vector>

#include <QObject>
#include <QMatrix4x4>
#include <QGLShaderProgram>

#include "shaders/shadermanager.h"

/*
 * Matrix stack class.
 * Manages transformation(scale, rotation) matrices.
 * Replacement for deprected glPopMatrix / glPushmatrix / etc functions.
 */

class MatrixStackManager : public QObject {
    Q_OBJECT
public:
    typedef QMatrix4x4 Matrix;

    MatrixStackManager(ShaderManager* sh_program);
    virtual ~MatrixStackManager() {}

    virtual void push();
    virtual void pop();

    // Access top stack matrix
    const Matrix& top() const;
    Matrix& top();

    // Projection Matrix get/set
    Matrix projectionMatrix() const;
    void setProjectionMatrix(const Matrix &m);
    // View Matrix get/set
    Matrix viewMatrix() const;
    void setViewMatrix(const Matrix &m);

public slots:
    void apply(); // Send matrices product to opengl/shader
    void clear();

protected:
    std::vector<Matrix> m_stack; // Top element is m_stack.back()
    Matrix m_projection, m_view;

    ShaderManager * m_shman;
};

#endif // MATRIXSTACK_H
