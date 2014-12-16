#pragma once

namespace glimac {

// Représente une sphère discrétisée centrée en (0, 0, 0) (dans son repère local)
// Son axe vertical est (0, 1, 0) et ses axes transversaux sont (1, 0, 0) et (0, 0, 1)
class TrackballCamera {
    // Alloue et construit les données (implantation dans le .cpp)
    //void build(GLfloat radius, GLsizei discLat, GLsizei discLong);

   void build(float m_fDistance, float m_fAngleXt, float m_fAngleY);

    public:
        // Constructeur: alloue le tableau de données et construit les attributs des vertex
        TrackballCamera(float m_fDistance, float m_fAngleXt, float m_fAngleY){
             build(m_fDistance, m_fAngleXt, m_fAngleY);
        }

        // permettant d'avancer / reculer la caméra. Lorsque delta est positif la caméra doit avancer, sinon elle doit reculer.
        void moveFront(float delta);
        // permettant de tourner latéralement autour du centre de vision.
        void rotateLeft(float degrees);
        // permettant de tourner verticalement autour du centre de vision.
        void rotateUp(float degrees);
        glm::mat4 getViewMatrix() const;

        float getDistance()const;
        float getAngleX()const;
        float getAngleY()const;

        float setDistance(float dist);
        float setAngleX(float angleX);
        float setAngleY(float angleY);

    private:
        float m_fDistance;
        float m_fAngleX;
        float m_fAngleY;
    };
}