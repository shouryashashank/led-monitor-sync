import re

def replace_led_terms(text,shift_by):
    def replace_match(match):
        led_number = int(match.group(1))
        new_led_number = led_number - shift_by
        return f"[LED_{new_led_number}]"

    updated_text = re.sub(r'\[LED_(\d+)\]', replace_match, text)
    return updated_text

def main():
    with open("led.txt", "r") as file:
        led_text = file.read()

    print(led_text)
    

    # set shift by
    shift_by = 13
    updated_led_text = replace_led_terms(led_text,shift_by)
    print(updated_led_text)

    with open("led.txt", "w") as file:
        file.write(updated_led_text)


if __name__=="__main__":
    main()