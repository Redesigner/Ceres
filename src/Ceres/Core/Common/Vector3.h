#pragma once

#include <string>

namespace Ceres
{
    /**
     * @brief 3-dimensional vector
     * 
     */
    struct Vector3
    {
        public:
            Vector3(float x, float y, float z);
            Vector3(float a);
            Vector3(const Vector3& vector);
            Vector3();
            ~Vector3();

            float X, Y, Z;

            static Vector3 Zero();
            static Vector3 Up();
            static float Epsilon() { return 0.0001; }
            
            /**
             * @brief Gets the length of the vector
             * @return float 
             */
            float Length() const;
            /**
             * @brief Gets the length of the vector, squared. Slightly faster than Length(), useful for comparing two vectors
             * @return float 
             */
            float LengthSquared() const;
            /**
             * @brief Gets the normalized vector
             * 
             * @return Vector3, or Vector3::Zero() if the vector cannot be normalized
             */
            Vector3 Normalize() const;
            /**
             * @brief Get the cross product of this and another vector
             * 
             * @param vector
             * @return Vector3 
             */
            Vector3 Cross(const Vector3& vector) const;
            /**
             * @brief Triple cross product of this and another vector
             * 
             * @param vector 
             * @return Vector3 
             */
            Vector3 Triple(const Vector3& vector) const;
            /**
             * @brief Dot product of this and another vector
             * 
             * @param vector 
             * @return float 
             */
            float Dot(const Vector3& vector) const;
            /**
             * @brief Angle between this and another vector
             * 
             * @param vector 
             * @return double representing the shortest rotation, in radians
             */
            double Angle(const Vector3& vector) const;

            Vector3& operator+=(const Vector3& vector);
            Vector3 operator+(const Vector3& vector) const;
            Vector3& operator-=(const Vector3& vector);
            Vector3 operator-(const Vector3& vector) const;
            Vector3 operator*(const Vector3& vector) const;
            Vector3 operator*(float scalar) const;
            Vector3 operator/(const Vector3& vector) const;
            Vector3 operator/(float scalar) const;
            Vector3 operator-() const;
            
            std::string ToString() const;

            bool operator==(const Vector3& vector) const;
            bool operator!=(const Vector3& vector) const;
        private:
    };

    Vector3 operator*(float scalar, const Vector3& vector);
}