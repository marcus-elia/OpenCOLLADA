/*
    Copyright (c) 2008 NetAllied Systems GmbH
	
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef __COLLADA_MAYA_TEXTURE_EXPORTER_H__
#define __COLLADA_MAYA_TEXTURE_EXPORTER_H__

#include "COLLADAMayaStableHeaders.h"
#include "COLLADAMayaDocumentExporter.h"
#include "COLLADAMayaDagHelper.h"
#include <map>

#include "COLLADAStreamWriter.h"
#include "COLLADALibraryEffects.h"
#include "COLLADAExtraTechnique.h"
#include "COLLADAExtra.h"
#include "COLLADAEffectProfile.h"
#include "COLLADAUtils.h"
#include "COLLADALibraryImages.h"

#include <maya/MFnDependencyNode.h>

namespace COLLADAMaya
{

    typedef std::map<String, COLLADA::Image*> ImageMap;

    /**
    * Class which manages the textures.
    */

    class EffectTextureExporter
    {

    private:

        /** The standard format for materials. */
        static const String FORMAT;

        /** A multi-texture blend mode. */
        enum Mode
        {
            NONE, /**< No blending. This is the default blend mode. */
            OVER, /**< Replaces the previous texture with the current one. */
            In, /**< ?. */
            OUt, /**< ?. */
            ADD, /**< Adds the color values from the previous texture to the current one. */
            SUBTRACT, /**< Substracts the color values from the current texture to the previous one. */
            MULTIPLY, /**< Modulates the previous texture with the current one. */
            DIFFERENCe, /**< Substracts the color values from the previous texture to the current one. */
            LIGHTEN, /**< ?. */
            DARKEN, /**< ?. */
            SATURATE, /**< ?. */
            DESATURATE, /**< ?. */
            ILLUMINATE, /**< ?. */

            UNKNOWN, /**< An unknown blend mode. */
            DEFAULT = NONE,
        };

        /** Pointer to the document exporter */
        DocumentExporter* mDocumentExporter;

        /** maps already exported image file names to the corresponding image id */
        ImageMap mExportedImageMap;

        /** true, if the <extra> and a <technique> tags are already open */
        bool techniqueIsOpen;

        /** The <extra> tag */
        COLLADA::Extra* mExtraSource;

        /** The <technique> tag */
        COLLADA::Technique* mTechniqueSource;

    public:

        /** Constructor. */
        EffectTextureExporter ( DocumentExporter* _documentExporter );
        virtual ~EffectTextureExporter();

        /**
        * Exports the current texture.
        * The parameters @shader and @attribute have to be set in the special case for bump maps:
        * export the bump height in the "amount" texture parameter.
        * Exists currently within the ColladaMax profile.
        */
        void exportTexture ( COLLADA::Texture* colladaTexture,
                             String channelSemantic,
                             const MObject &texture,
                             int blendMode,
                             int textureIndexconst );

        /**
        * Returns the std::map with the exported images.
        * @return const ImageMap*
        *   Returns a const pointer to the image map, managed and released
        *   in the class @EffectTextureExporter
        */
        const ImageMap* getExportedImageMap() const
        {
            return &mExportedImageMap;
        }

    private:

        /** Exports the texture image */
        String exportImage ( const MObject &texture );

        /** Dump a place2dTexture node */
        void add2DPlacement ( COLLADA::Texture* colladaTexture, MObject texture );

        /** Dump a place2dTexture 3DProjection */
        void add3DProjection ( COLLADA::Texture* colladaTexture, MObject projection );

        /** Opens an <extra> and a <technique> tag in the collada document */
        void openTechnique();

        /** Closes the <extra> and a <technique> tag in the collada document, if open */
        void closeTechnique();

        /** Adds an bool parameter into the <technique> tag */
        void addBoolParameter ( COLLADA::Texture* colladaTexture,
                                const char* plugName,
                                MFnDependencyNode &placement2d );

        /** Adds an float parameter into the <technique> tag */
        void addFloatParameter ( COLLADA::Texture* colladaTexture,
                                 const char* plugName,
                                 MFnDependencyNode &placement2d );

        /** Adds an angle parameter into the <technique> tag */
        void addAngleParameter ( COLLADA::Texture* colladaTexture,
                                 const char* plugName,
                                 MFnDependencyNode &placement2d );

        String getBlendMode ( int blendMode );

    };

}

#endif // __COLLADA_MAYA_TEXTURE_EXPORTER_H__