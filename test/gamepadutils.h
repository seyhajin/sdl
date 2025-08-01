/*
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/

/* Gamepad image */

#ifndef gamepadutils_h_
#define gamepadutils_h_

typedef struct GamepadImage GamepadImage;

typedef enum
{
    CONTROLLER_MODE_TESTING,
    CONTROLLER_MODE_BINDING,
} ControllerDisplayMode;

enum
{
    SDL_GAMEPAD_ELEMENT_INVALID = -1,

    /* ... SDL_GamepadButton ... */

    SDL_GAMEPAD_ELEMENT_AXIS_LEFTX_NEGATIVE = SDL_GAMEPAD_BUTTON_COUNT,
    SDL_GAMEPAD_ELEMENT_AXIS_LEFTX_POSITIVE,
    SDL_GAMEPAD_ELEMENT_AXIS_LEFTY_NEGATIVE,
    SDL_GAMEPAD_ELEMENT_AXIS_LEFTY_POSITIVE,
    SDL_GAMEPAD_ELEMENT_AXIS_RIGHTX_NEGATIVE,
    SDL_GAMEPAD_ELEMENT_AXIS_RIGHTX_POSITIVE,
    SDL_GAMEPAD_ELEMENT_AXIS_RIGHTY_NEGATIVE,
    SDL_GAMEPAD_ELEMENT_AXIS_RIGHTY_POSITIVE,
    SDL_GAMEPAD_ELEMENT_AXIS_LEFT_TRIGGER,
    SDL_GAMEPAD_ELEMENT_AXIS_RIGHT_TRIGGER,
    SDL_GAMEPAD_ELEMENT_AXIS_MAX,

    SDL_GAMEPAD_ELEMENT_NAME = SDL_GAMEPAD_ELEMENT_AXIS_MAX,
    SDL_GAMEPAD_ELEMENT_TYPE,
    SDL_GAMEPAD_ELEMENT_MAX,
};

#define HIGHLIGHT_COLOR         224, 255, 255, SDL_ALPHA_OPAQUE
#define HIGHLIGHT_TEXTURE_MOD   224, 255, 255
#define PRESSED_COLOR           175, 238, 238, SDL_ALPHA_OPAQUE
#define PRESSED_TEXTURE_MOD     175, 238, 238
#define SELECTED_COLOR          224, 255, 224, SDL_ALPHA_OPAQUE
#define GYRO_COLOR_RED          255, 0, 0, SDL_ALPHA_OPAQUE
#define GYRO_COLOR_GREEN        0, 255, 0, SDL_ALPHA_OPAQUE
#define GYRO_COLOR_BLUE         0, 0, 255, SDL_ALPHA_OPAQUE
#define GYRO_COLOR_ORANGE       255, 128, 0, SDL_ALPHA_OPAQUE

/* Shared layout constants */
#define BUTTON_PADDING          12.0f
#define MINIMUM_BUTTON_WIDTH 96.0f

/*  Symbol */
#define DEGREE_UTF8 "\xC2\xB0"
#define SQUARED_UTF8 "\xC2\xB2"
#define MICRO_UTF8   "\xC2\xB5"
/* Gamepad image display */

extern GamepadImage *CreateGamepadImage(SDL_Renderer *renderer);
extern void SetGamepadImagePosition(GamepadImage *ctx, float x, float y);
extern void GetGamepadImageArea(GamepadImage *ctx, SDL_FRect *area);
extern void GetGamepadTouchpadArea(GamepadImage *ctx, SDL_FRect *area);
extern void SetGamepadImageShowingFront(GamepadImage *ctx, bool showing_front);
extern SDL_GamepadType GetGamepadImageType(GamepadImage *ctx);
extern void SetGamepadImageDisplayMode(GamepadImage *ctx, ControllerDisplayMode display_mode);
extern float GetGamepadImageButtonWidth(GamepadImage *ctx);
extern float GetGamepadImageButtonHeight(GamepadImage *ctx);
extern float GetGamepadImageAxisWidth(GamepadImage *ctx);
extern float GetGamepadImageAxisHeight(GamepadImage *ctx);
extern int GetGamepadImageElementAt(GamepadImage *ctx, float x, float y);

extern void ClearGamepadImage(GamepadImage *ctx);
extern void SetGamepadImageElement(GamepadImage *ctx, int element, bool active);

extern void UpdateGamepadImageFromGamepad(GamepadImage *ctx, SDL_Gamepad *gamepad);
extern void RenderGamepadImage(GamepadImage *ctx);
extern void DestroyGamepadImage(GamepadImage *ctx);

/* Gamepad element display */

typedef struct GamepadDisplay GamepadDisplay;

extern GamepadDisplay *CreateGamepadDisplay(SDL_Renderer *renderer);
extern void SetGamepadDisplayDisplayMode(GamepadDisplay *ctx, ControllerDisplayMode display_mode);
extern void SetGamepadDisplayArea(GamepadDisplay *ctx, const SDL_FRect *area);
extern void SetGamepadDisplayGyroDriftCorrection(GamepadDisplay *ctx, float *gyro_drift_correction);
extern int GetGamepadDisplayElementAt(GamepadDisplay *ctx, SDL_Gamepad *gamepad, float x, float y);
extern void SetGamepadDisplayHighlight(GamepadDisplay *ctx, int element, bool pressed);
extern void SetGamepadDisplaySelected(GamepadDisplay *ctx, int element);
extern void RenderGamepadDisplay(GamepadDisplay *ctx, SDL_Gamepad *gamepad);
extern void DestroyGamepadDisplay(GamepadDisplay *ctx);

/* Gamepad type display */

enum
{
    SDL_GAMEPAD_TYPE_UNSELECTED = -1
};

typedef struct GamepadTypeDisplay GamepadTypeDisplay;

extern GamepadTypeDisplay *CreateGamepadTypeDisplay(SDL_Renderer *renderer);
extern void SetGamepadTypeDisplayArea(GamepadTypeDisplay *ctx, const SDL_FRect *area);
extern int GetGamepadTypeDisplayAt(GamepadTypeDisplay *ctx, float x, float y);
extern void SetGamepadTypeDisplayHighlight(GamepadTypeDisplay *ctx, int type, bool pressed);
extern void SetGamepadTypeDisplaySelected(GamepadTypeDisplay *ctx, int type);
extern void SetGamepadTypeDisplayRealType(GamepadTypeDisplay *ctx, SDL_GamepadType type);
extern void RenderGamepadTypeDisplay(GamepadTypeDisplay *ctx);
extern void DestroyGamepadTypeDisplay(GamepadTypeDisplay *ctx);

/* Joystick element display */

typedef struct JoystickDisplay JoystickDisplay;

extern JoystickDisplay *CreateJoystickDisplay(SDL_Renderer *renderer);
extern void SetJoystickDisplayArea(JoystickDisplay *ctx, const SDL_FRect *area);
extern char *GetJoystickDisplayElementAt(JoystickDisplay *ctx, SDL_Joystick *joystick, float x, float y);
extern void SetJoystickDisplayHighlight(JoystickDisplay *ctx, const char *element, bool pressed);
extern void RenderJoystickDisplay(JoystickDisplay *ctx, SDL_Joystick *joystick);
extern void DestroyJoystickDisplay(JoystickDisplay *ctx);

/* Simple buttons */

typedef struct GamepadButton GamepadButton;

extern GamepadButton *CreateGamepadButton(SDL_Renderer *renderer, const char *label);
extern void SetGamepadButtonLabel(GamepadButton *ctx, const char *label);
extern void SetGamepadButtonArea(GamepadButton *ctx, const SDL_FRect *area);
extern void GetGamepadButtonArea(GamepadButton *ctx, SDL_FRect *area);
extern void SetGamepadButtonHighlight(GamepadButton *ctx, bool highlight, bool pressed);
extern float GetGamepadButtonLabelWidth(GamepadButton *ctx);
extern float GetGamepadButtonLabelHeight(GamepadButton *ctx);
extern bool GamepadButtonContains(GamepadButton *ctx, float x, float y);
extern void RenderGamepadButton(GamepadButton *ctx);
extern void DestroyGamepadButton(GamepadButton *ctx);

/* Gyro element Display */

/* This is used as the initial noise tolerance threshold. It's set very close to zero to avoid divide by zero while we're evaluating the noise profile. Each controller may have a very different noise profile.*/
#define ACCELEROMETER_NOISE_THRESHOLD 1e-6f
/* The value below is based on observation of a Dualshock controller. Of all gamepads observed, the Dualshock (PS4) tends to have one of the noisiest accelerometers. Increase this threshold if a controller is failing to pass the noise profiling stage while stationary on a table. */
#define ACCELEROMETER_MAX_NOISE_G 0.075f
#define ACCELEROMETER_MAX_NOISE_G_SQ (ACCELEROMETER_MAX_NOISE_G * ACCELEROMETER_MAX_NOISE_G)

/* Gyro Calibration Phases */
typedef enum
{
    GYRO_CALIBRATION_PHASE_OFF,              /* Calibration has not yet been evaluated - signal to the user to put the controller on a flat surface before beginning the calibration process */
    GYRO_CALIBRATION_PHASE_NOISE_PROFILING,  /* Find the max accelerometer noise for a fixed period */
    GYRO_CALIBRATION_PHASE_DRIFT_PROFILING,  /* Find the drift while the accelerometer is below the accelerometer noise tolerance */
    GYRO_CALIBRATION_PHASE_COMPLETE,         /* Calibration has finished */
} EGyroCalibrationPhase;

typedef struct Quaternion Quaternion;
typedef struct GyroDisplay GyroDisplay;

extern void InitCirclePoints3D(void);
extern GyroDisplay *CreateGyroDisplay(SDL_Renderer *renderer);
extern void SetGyroDisplayArea(GyroDisplay *ctx, const SDL_FRect *area);
extern void SetGamepadDisplayIMUValues(GyroDisplay *ctx, float *gyro_drift_solution, float *euler_displacement_angles, Quaternion *gyro_quaternion, int reported_senor_rate_hz, int estimated_sensor_rate_hz, EGyroCalibrationPhase calibration_phase, float drift_calibration_progress_frac, float accelerometer_noise_sq, float accelerometer_noise_tolerance_sq);
extern GamepadButton *GetGyroResetButton(GyroDisplay *ctx);
extern GamepadButton *GetGyroCalibrateButton(GyroDisplay *ctx);
extern void RenderGyroDisplay(GyroDisplay *ctx, GamepadDisplay *gamepadElements, SDL_Gamepad *gamepad);
extern void DestroyGyroDisplay(GyroDisplay *ctx);

/* Working with mappings and bindings */

/* Return whether a mapping has any bindings */
extern bool MappingHasBindings(const char *mapping);

/* Return true if the mapping has a controller name */
extern bool MappingHasName(const char *mapping);

/* Return the name from a mapping, which should be freed using SDL_free(), or NULL if there is no name specified */
extern char *GetMappingName(const char *mapping);

/* Set the name in a mapping, freeing the mapping passed in and returning a new mapping */
extern char *SetMappingName(char *mapping, const char *name);

/* Get the friendly string for an SDL_GamepadType */
extern const char *GetGamepadTypeString(SDL_GamepadType type);

/* Return the type from a mapping, which should be freed using SDL_free(), or NULL if there is no type specified */
extern SDL_GamepadType GetMappingType(const char *mapping);

/* Set the type in a mapping, freeing the mapping passed in and returning a new mapping */
extern char *SetMappingType(char *mapping, SDL_GamepadType type);

/* Return true if a mapping has this element bound */
extern bool MappingHasElement(const char *mapping, int element);

/* Get the binding for an element, which should be freed using SDL_free(), or NULL if the element isn't bound */
extern char *GetElementBinding(const char *mapping, int element);

/* Set the binding for an element, or NULL to clear it, freeing the mapping passed in and returning a new mapping */
extern char *SetElementBinding(char *mapping, int element, const char *binding);

/* Get the element for a binding, or SDL_GAMEPAD_ELEMENT_INVALID if that binding isn't used */
extern int GetElementForBinding(char *mapping, const char *binding);

/* Return true if a mapping contains this binding */
extern bool MappingHasBinding(const char *mapping, const char *binding);

/* Clear any previous binding */
extern char *ClearMappingBinding(char *mapping, const char *binding);

#endif /* gamepadutils_h_ */
