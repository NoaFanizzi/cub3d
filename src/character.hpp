/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofanizz <nofanizz@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:06:22 by nofanizz          #+#    #+#             */
/*   Updated: 2025/12/26 16:07:14 by nofanizz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

class Character : public ICharacter
{
    private:
        std::string _name;
        AMateria* _inventory[4];

    public:
        Character(std::string const & name);
        Character(Character const & src);
        Character& operator=(Character const & rhs);
        virtual ~Character();

        virtual std::string const & getName() const;
        virtual void equip(AMateria* m);
        virtual void unequip(int idx);
        virtual void use(int idx, ICharacter& target);
};