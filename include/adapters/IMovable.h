#pragma once

class IMovable
{
public:
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~IMovable() = default;

    /**
     * @brief Получить текущую позицию объекта
     * @return Текущие координаты объекта
     */
    virtual int getPosition() const = 0;

    /**
     * @brief Установить новую позицию объекта
     * @param position Новые координаты
     */
    virtual void setPosition(const int& position) = 0;

        /**
     * @brief Получить вектор скорости объекта
     * @custom_impl MovableImplementations::getVelocity
     * @return Вектор скорости с учетом направления и модуля скорости
     */
    virtual int getVelocity() const = 0;

};
