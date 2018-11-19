#pragma once

#ifndef __FORWARD_RENDERER__
#define __FORWARD_RENDERER__

#include "common/Rendering/Renderer.h"

/*! \brief A multi-pass forward renderer with lights. 
 *
 *  More details about what a multi-pass forward renderer is can be found in the documentation for the Render() function. Do note that this class will not support
 *  transparent objects out of the box! You will have to find a way to handle them if you want to display transparent objects properly.
 */
class ForwardRenderer: public Renderer
{
public:
    /*! \brief Stores the input scene and the input camera for use for rendering. 
     *
     *  Calls the base class constructor, Renderer::Renderer().
     */
    ForwardRenderer(std::shared_ptr<class Scene> inputScene, std::shared_ptr<class Camera> inputCamera);

    /*! \brief Just a day in the life of a destructor.
     */
    virtual ~ForwardRenderer();

    /*! \brief Loads the data that the forward renderer needs.
     *
     *  Loads the depth prepass shader. See the documentation of Render() for why it is necessary.
     */ 
    virtual void Initialize() override;

    /*! \brief Renders a frame using a multi-pass forward renderer with all the lights in the scene.
     *
     *  Note that in the multi-pass forward renderer, there is no limit to how many lights you may use; however, once the number of lights becomes too high,
     *  you will start to see a significant drop in frames per second. In our implementation of the multi-pass forward renderer, assuming that there are \f$N\f$
     *  lights, the renderer will perform \f$ N + 2 \f$ passes through every object in the scene. For every draw call, the multi-pass forward renderer will 
     *  perform additive blending of both the RGB and alpha channels to compute the new color in the color buffer. The render pass stages are as follows:
     *
     *  -# The depth preprocess stage. Without this stage, some objects will transparent even if they are not actually. Let's say a relative large and complex object
     *  has parts that are facing towards the camera but are occluded. Then let's say that the light vertex/fragment shader processes that part first and then processes
     *  the occluder parts later. With additive blending turned on, the colors will be mixed! Turning additive blending is not an option for a multi-pass forward
     *  renderer. Instead what we want to do is to perform an initial "depth preprocess" pass through every object in the scene. By doing this, we write the 
     *  final depth of an object to the depth buffer. In the subsequent render passes, we will only write to the color buffer is the depth value is less than or equal to the 
     *  value already stored in the depth buffer. Since we ran the depth preprocess pass on EVERY object in the scene, we are guaranteed that the value stored in the depth
     *  buffer is the smallest possible value for that pixel. So if a render pass passes the depth buffer check, it can know for sure that it is safe to write to the color
     *  buffer and that there won't be another object occluding it. It is important to note that depth is stored as a floating point value and with floating point values comes
     *  numerical imprecision which can result in <a href="https://en.wikipedia.org/wiki/Z-fighting">z-fighting</a>. As a result, we use
     *  <a href="https://www.opengl.org/sdk/docs/man/html/glPolygonOffset.xhtml">glPolygonOffset</a> to offset the depth values ever so slightly to prevent z-fighting from
     *  occurring. The amount that we offset ~should~ not be enough to cause problems with fragments passing the depth buffer test that otherwise should not.
     *
     *  -# The "global lighting" phase. This phase takes care of the ambient color of the material (Note: it might make more sense for the ambient color be a property of the
     *  light and not the material). Regardless, this phase will take care of the color that should only be added to the object once regardless of how many lights shine upon
     *  it. Good examples of things that would go in this stage are the ambient and emissive colors.
     *
     *  -# Finally, the rest of the lighting passes are dedicated to performing a normal render pass with a light in the scene. The rendering object in question is queried for
     *  the correct shader to use, the shader is then setup by the rendering object and the scene object, and finally the object is rendered and the resulting fragment colors
     *  are correctly blended into the color buffer.
     *
     *  Still confused? Ask on Piazza!
     */
    virtual void Render() override;
};

#endif
