#pragma once

#include "Base/IComponent.h"

#include "../Common/Matrix.h"

namespace Ceres
{
    /**
     * @brief A camera object
     * 
     */
    class CameraComponent : public IComponent
    {
        public:
            CameraComponent(int width, int height, float fOV, float near, float far);
            CameraComponent();
            ~CameraComponent();

            bool virtual ReceiveMessage(Message& message) override;

            /**
             * @brief Get the Matrix object associated with this camera's transformation
             * 
             * @return const Matrix& 
             */
            const Matrix& GetMatrix();
            /**
             * @brief Get the Matrix object associated with this camera's rotation only
             * 
             * @return const Matrix& 
             */
            const Matrix& GetRotationMatrix();
            /**
             * @brief Get the current position of the camera, in world space
             * 
             * @return const Vector3 
             */
            const Vector3 GetPosition() const;
            /**
             * @brief Get the current position of whatever the camera is looking at, in world space
             * 
             * @return const Vector3 
             */
            const Vector3 GetFocalPoint() const;

            const float GetFOV() const;
            void SetFOV(const float fOV);

            /**
             * @brief Set the dimensions of the camera, in pixels
             * 
             * @param width 
             * @param height 
             */
            void SetResolution(unsigned int width, unsigned int height);

            void SetClipRange(float start, float end);

            Vector3 FocalPoint;
            Vector3 Rotation = Vector3(-0.2f, 0.0f, 0.0f);
            Vector3 Offset = Vector3(0.0f, -7.0f, 0.0f);

        private:
            void setPosition(const Vector3& position);
            void translate(const Vector3& translation);
            void rotate(const Vector3& rotation);

            Matrix _matrix;
            Matrix _viewRotation;
            Matrix _projection;
            Vector3 _velocityOffset;
            /// The velocity of our parent, for when we are tracking slightly behind the object
            Vector3 _velocity;

            // Cache on-data-requested flags
            bool _regenViewMatrix = true;
            bool _regenRotationMatrix = true;
            bool _regenProjectionMatrix = true;

            float _fOV = 90.0f;
            unsigned int _width;
            unsigned int _height;
            float _clipStart = 0.1f;
            float _clipEnd = 100.0f;
    };
}