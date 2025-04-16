import logging


class ColorFormatter(logging.Formatter):
    COLORS = {
        'DEBUG': '\033[90m',        # Bright Black / Gray
        'INFO': '\033[92m',         # Bright Green
        'WARNING': '\033[93m',      # Bright Yellow
        'ERROR': '\033[91m',        # Bright Red
        'CRITICAL': '\033[1;91m',   # Bold Bright Red
    }
    RESET = '\033[0m'

    def format(self, record):
        levelname = record.levelname
        short_level = levelname[:4].upper()
        color = self.COLORS.get(levelname, '')
        record.short_levelname = f"{color}[{short_level}]{self.RESET}"

        return super().format(record)

formatter = ColorFormatter('%(short_levelname)s %(message)s')
handler = logging.StreamHandler()
handler.setFormatter(formatter)
logger = logging.getLogger("mylogger")
logger.setLevel(logging.DEBUG)
logger.addHandler(handler)
