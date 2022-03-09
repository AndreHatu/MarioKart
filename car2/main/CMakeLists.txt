set(srcs "main.c" "pwm.c"
    )

idf_component_register(
    SRCS  ${srcs}
    INCLUDE_DIRS "."
)