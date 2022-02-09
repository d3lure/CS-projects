import pygame
import tkinter as tk
from tkinter import *
from WorldModule import World


def main():

    WIDTH, HEIGHT = 600, 700
    ROWS, COLS = 10, 10
    NUM_ORGANISMS = 20

    WIN = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("Maciej Matuszewski 184480")
    pygame.init()

    smallfont = pygame.font.SysFont('Arial', 20)

    save_text = smallfont.render('Save', True, (255, 255, 255))
    load_text = smallfont.render('Load', True, (255, 255, 255))
    new_text = smallfont.render('New', True, (255, 255, 255))
    logs_text = smallfont.render('Logs', True, (255, 255, 255))

    pygame.draw.rect(WIN, (0, 200, 100), (0, HEIGHT - 100, 100, 50))
    pygame.draw.rect(WIN, (50, 100, 200), (WIDTH // 4, HEIGHT - 100, 100, 50))
    pygame.draw.rect(WIN, (100, 50, 200), (WIDTH // 2, HEIGHT - 100, 100, 50))
    pygame.draw.rect(WIN, (0, 100, 200), (3 * WIDTH // 4, HEIGHT - 100, 100, 50))

    p = World(ROWS, COLS, WIN)
    p.random_world_generator(NUM_ORGANISMS)

    log_win = tk.Tk()
    txt = tk.Text(log_win, height=15, width=40)
    txt.pack()
    Button(log_win, text="Quit", command=log_win.withdraw, fg="white",
           bg="red", width=20).pack(pady=10)
    log_win.withdraw()

    clock = pygame.time.Clock()
    run = True
    while run:
        clock.tick(30)
        for event in pygame.event.get():
            keys_pressed = pygame.key.get_pressed()

            if event.type == pygame.QUIT:
                p.save_to_file('saves/default_save.txt')
                run = False

            if event.type == pygame.MOUSEBUTTONDOWN:
                pos = pygame.mouse.get_pos()

                if 0 < pos[0] < WIDTH and 0 < pos[1] < HEIGHT-100:
                    row, col = p.get_pos_mouse(pos)
                    p.add_org_window(row, col)

                if pos[0] >= 0 and pos[1] >= HEIGHT-100:
                    if pos[0] <= 100 and pos[1] <= HEIGHT-50:
                        p = World(ROWS, COLS, WIN)
                        p.random_world_generator(NUM_ORGANISMS)

                if pos[0] >= WIDTH//4 and pos[1] >= HEIGHT-100:
                    if pos[0] <= WIDTH//4 + 100 and pos[1] <= HEIGHT-50:
                        file = p.prompt_file()
                        p.load_from_file(file)

                if pos[0] >= WIDTH//2 and pos[1] >= HEIGHT-100:
                    if pos[0] <= WIDTH//2 + 100 and pos[1] <= HEIGHT-50:
                        file = p.prompt_save_file()
                        p.save_to_file(file)

                if pos[0] >= 3*WIDTH//4 and pos[1] >= HEIGHT-100:
                    if pos[0] <= 3*WIDTH//4 + 100 and pos[1] <= HEIGHT-50:
                        log_win.update()
                        log_win.deiconify()

            if event.type == pygame.KEYDOWN:

                if keys_pressed[pygame.K_LEFT]:
                    p.set_human_direction('LEFT')

                elif keys_pressed[pygame.K_DOWN]:
                    p.set_human_direction('DOWN')

                elif keys_pressed[pygame.K_RIGHT]:
                    p.set_human_direction('RIGHT')

                elif keys_pressed[pygame.K_UP]:
                    p.set_human_direction('UP')

                elif keys_pressed[pygame.K_SPACE]:
                    if p.get_human():
                        p.get_human().immortality()
                        p.set_human_direction(None)

                p.make_turn()

                if log_win is not None:
                    txt.delete("1.0", "end")
                    txt.insert(tk.END, p.get_feed())
                    log_win.update()

            WIN.blit(new_text, (0, HEIGHT - 3 * p.square_size // 2))
            WIN.blit(load_text, (WIDTH // 4, HEIGHT - 3 * p.square_size // 2))
            WIN.blit(save_text, (WIDTH // 2, HEIGHT - 3 * p.square_size // 2))
            WIN.blit(logs_text, (3 * WIDTH // 4, HEIGHT - 3 * p.square_size // 2))

            pygame.display.update()

    pygame.quit()


if __name__ == "__main__":
    main()
