LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := spine_static

LOCAL_MODULE_FILENAME := libspine

LOCAL_SRC_FILES := Animation.c \
AnimationState.c \
AnimationStateData.c \
Array.c \
Atlas.c \
AtlasAttachmentLoader.c \
Attachment.c \
AttachmentLoader.c \
Bone.c \
BoneData.c \
BoundingBoxAttachment.c \
ClippingAttachment.c \
Color.c \
Event.c \
EventData.c \
extension.c \
IkConstraint.c \
IkConstraintData.c \
Json.c \
MeshAttachment.c \
PathAttachment.c \
PathConstraint.c \
PathConstraintData.c \
PointAttachment.c \
RegionAttachment.c \
Skeleton.c \
SkeletonBinary.c \
SkeletonBounds.c \
SkeletonClipping.c \
SkeletonData.c \
SkeletonJson.c \
Skin.c \
Slot.c \
SlotData.c \
TransformConstraint.c \
TransformConstraintData.c \
Triangulator.c \
VertexAttachment.c \
VertexEffect.c \
AttachmentVertices.cpp \
Cocos2dAttachmentLoader.cpp \
SkeletonAnimation.cpp \
SkeletonBatch.cpp \
SkeletonRenderer.cpp \
SkeletonTwoColorBatch.cpp \
spine-cocos2dx.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_STATIC_LIBRARIES := cocos2dx_internal_static

include $(BUILD_STATIC_LIBRARY)
