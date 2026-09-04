idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES definitions audio bases gyro powermgmt sensors visual
)
