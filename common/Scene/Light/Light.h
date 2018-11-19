#pragma once

#ifndef __LIGHT__
#define __LIGHT__

#include "common/Scene/SceneObject.h"

/*! \brief Generic light class.
 *
 *  Note that the "Light" class only holds the properties related to the orientation and shape of the camera in world space.
 *  The actual "light" of the Light object is stored within a LightProperties structure. The Light class acts as a point light.
 */
class Light: public SceneObject
{
public:
    /*! \brief The different types of light.
     *
     *  If you ever want to create a new type of light, you should add a new entry into the LightType enum and then have the 
     *  ShaderProgram subclass handle that LightType properly. Note that the LightType::GLOBAL enum is used by the BlinnPhongShader to 
     *  handle global light (if any). You can ignore this if your shader does not have any global light that should only be applied once
     *  per object.
     */
    enum class LightType {
        GLOBAL = 0,
        POINT,
        DIRECTIONAL,
        HEMISPHERE,
        IBL
    };

    /*! \brief Constructs a light from user-specified properties and a light type.
     *  \param inProperties The LightProperties structure. The type of this property is dependent on what shader is being used.
     *  \param type The type of light as enumerated in the LightType enum.
     *
     *  Subclasses of the Light class should pass in the appropriate LightType to the base class constructor.
     *  Note that a point light should probably be its own subclass instead of just hijacking the base class.
     */
    Light(std::unique_ptr<struct LightProperties> inProperties, LightType type = LightType::POINT);
    virtual ~Light();

    /*! \brief Returns the attenuation parameters for the light.
     *  \param constant Reference where the constant attenuation will be written to.
     *  \param linear Reference where the linear attenuation will be written to.
     *  \param quadratic Reference where the quadratic attenuation will be written to.
     *
     *  Let us define \f$d\f$ as the distance a vertex is from the light. Furthermore, let's define
     *  \f$c\f$ as the constant attenuation, \f$l\f$ as the linear attenuation, and \f$q\f$ as the quadratic attenuation.
     *  Then the light's intensity will be multiplied by \f$\frac{1}{c + d l + d^2 l}\f$.
     */
    void GetAttenuation(float& constant, float& linear, float& quadratic) const;

    void SetConstantAttenuation(float inValue);
    void SetLinearAttenuation(float inValue);
    void SetQuadraticAttenuation(float inValue);

    LightType GetLightType() const { return lightType; }

    const struct LightProperties* GetPropertiesRaw() const;
    
    /*! \brief Sets up the shader to have the necessary properties for a given type of light.
     *  \param program The shader to setup.
     *  \warning Deprecated.
     *
     *  For a point light, the only thing that is necessary is the light's position.
     */ 
    virtual void SetupShaderUniforms(const class ShaderProgram* program) const;
private:
    static const std::string LIGHT_UNIFORM_NAME;
    std::unique_ptr<struct LightProperties> properties;

    LightType lightType;

    // Attenuation
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

#endif
