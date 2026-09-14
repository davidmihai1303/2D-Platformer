//
// Created by David Mihailescu on 13/09/2026.
//

#include "terrain/TerrainCollision.hpp"

#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>

bool expectBounds(const char* scenario, const sf::FloatRect& actual, const sf::FloatRect& expected) {
    // These examples use whole pixels, which can be compared exactly as floats.
    if (actual == expected) {
        return true;
    }

    std::cerr << "FAIL: " << scenario << '\n'
              << "  expected position (" << expected.position.x << ", " << expected.position.y << "), size ("
              << expected.size.x << ", " << expected.size.y << ")\n"
              << "  actual position (" << actual.position.x << ", " << actual.position.y << "), size ("
              << actual.size.x << ", " << actual.size.y << ")\n";
    return false;
}

bool expectNoContacts(const char* scenario, const TerrainContacts& contacts) {
    if (!contacts.floor && !contacts.ceiling && !contacts.leftWall && !contacts.rightWall) {
        return true;
    }

    std::cerr << "FAIL: " << scenario << " should have no contacts\n"
              << "  actual floor=" << contacts.floor << ", ceiling=" << contacts.ceiling
              << ", leftWall=" << contacts.leftWall << ", rightWall=" << contacts.rightWall << '\n';
    return false;
}

bool expectInvalidTerrain(const char* scenario, const sf::FloatRect& solid) {
    try {
        TerrainCollision({solid});
    } catch (const std::invalid_argument&) {
        return true;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << scenario << " threw another exception: " << error.what() << '\n';
        return false;
    }

    std::cerr << "FAIL: " << scenario << " did not throw std::invalid_argument\n";
    return false;
}

bool expectInvalidMovement(const char* scenario, const sf::FloatRect& body, const sf::Vector2f displacement) {
    try {
        TerrainCollision::resolveMovement(body, displacement);
    } catch (const std::invalid_argument&) {
        return true;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << scenario << " threw another exception: " << error.what() << '\n';
        return false;
    }

    std::cerr << "FAIL: " << scenario << " did not throw std::invalid_argument\n";
    return false;
}

int main() {
    int failures = 0;
    // World-pixel rectangle: top-left (10, 20), width 16, height 32.
    const sf::FloatRect startBounds{{10.f, 20.f}, {16.f, 32.f}};

    // Positive X moves right; negative Y moves up. With no obstacles, apply the full request.
    const TerrainMove moved = TerrainCollision::resolveMovement(startBounds, {5.f, -3.f});
    if (!expectBounds("empty terrain: full displacement", moved.bounds, {{15.f, 17.f}, {16.f, 32.f}})) {
        ++failures;
    }
    if (!expectNoContacts("empty terrain: full displacement", moved.contacts)) {
        ++failures;
    }

    const TerrainMove stationary = TerrainCollision::resolveMovement(startBounds, {0.f, 0.f});
    if (!expectBounds("empty terrain: zero displacement", stationary.bounds, startBounds)) {
        ++failures;
    }
    if (!expectNoContacts("empty terrain: zero displacement", stationary.contacts)) {
        ++failures;
    }

    const sf::FloatRect negativeSolid{{-20.f, -10.f}, {16.f, 32.f}};
    try {
        const TerrainCollision terrain({negativeSolid});
        if (!expectBounds("negative terrain position", terrain.getSolids().at(0), negativeSolid)) {
            ++failures;
        }
    } catch (const std::exception& error) {
        std::cerr << "FAIL: negative terrain position was rejected: " << error.what() << '\n';
        ++failures;
    }

    try {
        const TerrainMove negativeMove = TerrainCollision::resolveMovement(negativeSolid, {5.f, -3.f});
        if (!expectBounds("negative body position", negativeMove.bounds, {{-15.f, -13.f}, {16.f, 32.f}})) {
            ++failures;
        }
        if (!expectNoContacts("negative body position", negativeMove.contacts)) {
            ++failures;
        }
    } catch (const std::exception& error) {
        std::cerr << "FAIL: negative body position was rejected: " << error.what() << '\n';
        ++failures;
    }

    const float nan = std::numeric_limits<float>::quiet_NaN();
    const float infinity = std::numeric_limits<float>::infinity();

    if (!expectInvalidTerrain("terrain with zero width", {{0.f, 0.f}, {0.f, 32.f}})) {
        ++failures;
    }
    if (!expectInvalidTerrain("terrain with negative height", {{0.f, 0.f}, {16.f, -32.f}})) {
        ++failures;
    }
    if (!expectInvalidTerrain("terrain with NaN y position", {{0.f, nan}, {16.f, 32.f}})) {
        ++failures;
    }
    if (!expectInvalidTerrain("terrain with infinite width", {{0.f, 0.f}, {infinity, 32.f}})) {
        ++failures;
    }
    if (!expectInvalidMovement("body with zero height", {{0.f, 0.f}, {16.f, 0.f}}, {0.f, 0.f})) {
        ++failures;
    }
    if (!expectInvalidMovement("body with NaN x position", {{nan, 0.f}, {16.f, 32.f}}, {0.f, 0.f})) {
        ++failures;
    }
    if (!expectInvalidMovement("infinite x displacement", startBounds, {infinity, 0.f})) {
        ++failures;
    }
    if (!expectInvalidMovement("NaN y displacement", startBounds, {0.f, nan})) {
        ++failures;
    }

    // CTest uses the process exit code: zero passes, any nonzero value fails.
    return failures == 0 ? 0 : 1;
}
