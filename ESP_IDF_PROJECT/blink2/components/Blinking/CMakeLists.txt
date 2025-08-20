file(GLOB SRCS "Src/*.cc")
idf_component_register(SRCS ${SRCS}
                    INCLUDE_DIRS "Include"
                    REQUIRES driver)
